#include "ShapeState.h"
#include "AssesmentState.h"
#include <iostream>

#include <QtGui>
#include <QtCore>
#include <random>
#include <QFile>
#include <QTextStream>

const size_t POINT_COUNT = 20;
const float RADIUS = 300.f;
const std::chrono::seconds SHAPEDURATION(8);

void ShapeState::init(QWidget* widget)
{
    m_start = std::chrono::system_clock::now();
    m_widget = widget;

    std::cout << "Shape init " << std::endl;

    std::random_device rd;
    std::default_random_engine ren(rd());
    std::uniform_real_distribution<float> rnd(0.f, 1.f);

    auto m_sharpness = rnd(ren);
    auto m_ltcr= rnd(ren);


        QString filename = "/home/vv/Desktop/Data.txt";
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << m_sharpness <<"," << m_ltcr << endl;
        }


    m_points = assignLTC(generatePoints(POINT_COUNT, RADIUS, m_sharpness), m_ltcr);
    m_shape = buildShape(m_points);
}

void ShapeState::process()
{
    std::cout << "Shape process" << std::endl;

    auto now = Clock::now();
    if (now - m_last_target_tp > std::chrono::milliseconds(1000))
    {
        m_last_target_tp = now;

        std::random_device rd;
        std::default_random_engine e1(rd());
        std::uniform_real_distribution<float> rnd(0.f, 1.f);

        float x = rnd(e1) * (m_widget->width() - m_shape.width());
        float y = rnd(e1) * (m_widget->height() - m_shape.height());

        m_target = QPointF(x, y);
    }

//    auto speed = m_speed / 700.f;
    m_position = (m_position + (m_target - m_position) * m_speed);

    QPainter painter(m_widget);
    painter.drawImage(m_position, m_shape);
}

std::unique_ptr<State> ShapeState::finish()
{
    auto now = std::chrono::system_clock::now();
    if (now - m_start >= SHAPEDURATION)
    {
        return std::unique_ptr<State>(new AssesmentState);
    }
    else
    {
        return nullptr;
    }
}





std::vector<ShapeState::Point> ShapeState::generatePoints(size_t count, float radius, float sharpness)
{
    float angleInc = 2.f * M_PI / count;

    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_real_distribution<float> daRnd(-angleInc / 3.f, angleInc / 3.f);
    std::uniform_real_distribution<float> radiusRnd(radius * ((1.f - sharpness) * 0.7f + 0.1f), radius);

    std::vector<Point> points;

    float angle = 0.f;
    for (size_t i = 0; i < count; i++)
    {
        float deltaAngle = daRnd(e1);
        float radius = radiusRnd(e1);

        float x = std::cos(angle + deltaAngle) * radius;
        float y = std::sin(angle + deltaAngle) * radius;

        Point p;
        p.point = QPointF(x, y);
        p.t = 0.f;
        points.push_back(p);

        angle += angleInc;
    }

    return points;
}

std::vector<ShapeState::Point> ShapeState::assignLTC(const std::vector<ShapeState::Point>& _points, float ltcr)
{
    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_real_distribution<float> ltcrRnd(0, 1);

    std::vector<Point> points = _points;

    for (auto& p: points)
    {
        if (ltcrRnd(e1) >= ltcr)
        {
            p.t = 0.f;
        }
        else
        {
            p.t = m_curviness;
        }
    }

    return points;
}


void ShapeState::getControlPoints(QPointF p0, QPointF p1, QPointF p2, float t, QPointF& c0, QPointF& c1)
{
    auto d01 = std::sqrt(std::pow(p1.x()-p0.x(),2.f)+std::pow(p1.y()-p0.y(),2));
    auto d12=std::sqrt(std::pow(p2.x()-p1.x(),2)+std::pow(p2.y()-p1.y(),2));
    auto fa=t*d01/(d01+d12);   // scaling factor for triangle Ta
    auto fb=t*d12/(d01+d12);   // ditto for Tb, simplifies to fb=t-fa
    auto p0x=p1.x()-fa*(p2.x()-p0.x());    // x2-x0 is the width of triangle T
    auto p0y=p1.y()-fa*(p2.y()-p0.y());    // y2-y0 is the height of T
    auto p1x=p1.x()+fb*(p2.x()-p0.x());
    auto p1y=p1.y()+fb*(p2.y()-p0.y());
    c0 = QPointF(p0x, p0y);
    c1 = QPointF(p1x, p1y);
}

struct fillpixelinfo
{
   int y, xl, xr, dy;
};

#define PUSH(py, pxl, pxr, pdy) \
{ \
    struct fillpixelinfo p;\
    if (((py) + (pdy) >= 0) && ((py) + (pdy) < image.height()))\
    {\
        p.y = (py);\
        p.xl = (pxl);\
        p.xr = (pxr);\
        p.dy = (pdy);\
        stack.push_back(p); \
    }\
}

#define POP(py, pxl, pxr, pdy) \
{\
    struct fillpixelinfo p = stack.back();\
    stack.pop_back();\
    (py) = p.y + p.dy;\
    (pxl) = p.xl;\
    (pxr) = p.xr;\
    (pdy) = p.dy;\
}

QImage ShapeState::floodFill(const QImage& img, const QPoint &pos, const QRgb &newColor)
{
   QImage image = img.copy();

   int x = pos.x(), y = pos.y();
   const QRgb oldColor = image.pixel(x, y);


   std::vector<fillpixelinfo> stack;

   int l, x1, x2, dy;

   if ((x >= 0) && (x < image.width()) && (y >= 0) && (y < image.height()))
   {
       if (qAlpha(oldColor) == 0xFF)
       {
           return image;
       }
       PUSH(y, x, x, 1);
       PUSH(y + 1, x, x, -1);
       while (!stack.empty())
       {
           POP(y, x1, x2, dy);
           for (x = x1; (x >= 0) && qAlpha(image.pixel(x, y)) != 0xFF; x--)
           {
               image.setPixel(x, y, newColor);
           }
           if (x >= x1)
           {
               goto skip;
           }
           l = x + 1;
           if (l < x1)
           {
               PUSH(y, l, x1 - 1, -dy);
           }
           x = x1 + 1;
           do
           {
               for (; (x < image.width()) && qAlpha(image.pixel(x, y)) != 0xFF; x++)
               {
                   image.setPixel(x, y, newColor);
               }
               PUSH(y, l, x - 1, dy);
               if (x > x2 + 1)
               {
                   PUSH(y, x2 + 1, x - 1, -dy);
               }
skip:
               for (x++; x <= x2 && qAlpha(image.pixel(x, y)) == 0xFF; x++)
               {
                   /* empty */ ;
               }
               l = x;
           } while (x <= x2);
       }
   }
   return image;
}

QImage ShapeState::buildShape(const std::vector<Point>& _points)
{
    if (_points.empty())
    {
        return QImage();
    }

    size_t n = _points.size();
    std::vector<Point> points = _points;

    QColor shapeColor(84, 84, 84);

    QPointF min, max;
    min.setX(std::numeric_limits<float>::max());
    min.setY(std::numeric_limits<float>::max());
    max.setX(std::numeric_limits<float>::lowest());
    max.setY(std::numeric_limits<float>::lowest());
    for (const auto& p: points)
    {
        max.setX(std::max(max.x(), p.point.x()));
        max.setY(std::max(max.y(), p.point.y()));
        min.setX(std::min(min.x(), p.point.x()));
        min.setY(std::min(min.y(), p.point.y()));
    }

    {
        //re-center the points
        QPointF center = (max + min) / 2.f;
        for (auto& p: points)
        {
            p.point -= center;
        }
    }

    QSizeF imageSize((max - min).x(), (max - min).y());
    imageSize += QSize(200, 200);
    QPointF imageCenter(imageSize.width() / 2.f, imageSize.height() / 2.f);

    QImage image = QImage(imageSize.toSize(), QImage::Format_RGBA8888_Premultiplied);
    image.fill(0);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen(shapeColor, 3.f);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);

    QPainterPath path;

    //   Append and prepend knots and control points to close the curve

    {
        auto last = points.back();
        points.push_back(*(points.begin() + 0));
        points.push_back(*(points.begin() + 1));
        points.insert(points.begin(), last);
    }

    std::vector<QPointF> cp;
    for(size_t i = 0; i < n; i++)
    {
        QPointF cp0, cp1;
        getControlPoints(points[i].point, points[i + 1].point, points[i + 2].point, points[i].t, cp0, cp1);
        cp.push_back(cp0);
        cp.push_back(cp1);
    }
    cp.push_back(cp.front());
    for(size_t i = 1; i < n + 1; i++)
    {
        //var color=HSVtoRGB(Math.floor(240*(i-2)/(n-2)),0.8,0.8);
        //if(!showDetails){color="#555555"}
        //ctx.strokeStyle=hexToCanvasColor(color,0.75);
        path.moveTo(imageCenter + points[i].point);
        path.cubicTo(imageCenter + cp[i*2 - 1], imageCenter + cp[i*2], imageCenter + points[i + 1].point);
    }

    path.setFillRule(Qt::WindingFill);
    painter.drawPath(path);

    return floodFill(image, imageCenter.toPoint(), shapeColor.rgb());
}
