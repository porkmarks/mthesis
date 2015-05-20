#include "Splines.h"
#include "ui_Splines.h"

const float MAX_CURVATURE = 20.f;

Splines::Splines(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Splines)
{
    ui->setupUi(this);

    connect(ui->ltcr, &QSlider::valueChanged, [this](int value)
    {
       m_ltcr = value / 100.f;
    });

    connect(ui->applyLTCR, &QPushButton::released, [this]()
    {
       m_points = assignLTC(m_points, m_ltcr);
       update();
    });

    connect(ui->newShape, &QPushButton::released, [this]()
    {
       m_points = assignLTC(generatePoints(20, 200), m_ltcr);
       update();
    });
}

Splines::~Splines()
{
    delete ui;
}

std::vector<Splines::Point> Splines::generatePoints(size_t count, float radius)
{
    float angleInc = 2.f * M_PI / count;

    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_real_distribution<float> daRnd(-angleInc / 3.f, angleInc / 3.f);
    std::uniform_real_distribution<float> radiusRnd(radius / 2.f, radius);

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

std::vector<Splines::Point> Splines::assignLTC(const std::vector<Splines::Point>& _points, float ltcr)
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


void Splines::paintEvent(QPaintEvent*)
{
    auto image = buildShape(m_points);

    QPainter painter(this);
    painter.drawImage(QPointF(100, 100), image);

    //make the splines
  //  drawSpline(painter, start, end, c0, c1);
}

void Splines::getControlPoints(QPointF p0, QPointF p1, QPointF p2, float t, QPointF& c0, QPointF& c1)
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

QImage Splines::floodFill(const QImage& img, const QPoint &pos, const QRgb &newColor)
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

QImage Splines::buildShape(const std::vector<Point>& _points)
{
    if (_points.empty())
    {
        return QImage();
    }

    size_t n = _points.size();
    std::vector<Point> points = _points;

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

    QPen pen(Qt::white, 3.f);
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

    return floodFill(image, imageCenter.toPoint(), qRgb(255, 255, 255));
}


