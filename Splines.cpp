#include "Splines.h"
#include "ui_Splines.h"

const float MAX_CURVATURE = 20.f;

Splines::Splines(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Splines)
{
    ui->setupUi(this);

    connect(ui->curviness, &QSlider::valueChanged, [this](int value)
    {
       m_curviness = value / 1000.f;
       update();
    });
}

Splines::~Splines()
{
    delete ui;
}

void Splines::paintEvent(QPaintEvent*)
{
     QPainter painter(this);


     std::vector<QPointF> polyPoints =
     {
        {30.f, 300.f},
        {40.f, 140.f},
        {75.f, 110.f},
        {80.f, 200.f},
        {140.f, 150.f},
        {150.f, 120.f},
        {300.f, 220.f},
        {360.f, 280.f},
        {30.f, 300.f},

     };

    drawShape(painter, m_curviness, polyPoints);

    //make the splines
  //  drawSpline(painter, start, end, c0, c1);
}

void getControlPoints(QPointF p0, QPointF p1, QPointF p2, float t, QPointF& c0, QPointF& c1)
{
    auto d01 = std::sqrt(std::pow(p1.x()-p0.x(),2.f)+std::pow(p1.y()-p0.y(),2));
    auto d12=std::sqrt(std::pow(p2.x()-p1.x(),2)+std::pow(p2.y()-p1.y(),2));
    auto fa=t*d01/(d01+d12);   // scaling factor for triangle Ta
    auto fb=t*d12/(d01+d12);   // ditto for Tb, simplifies to fb=t-fa
    auto p1x=p1.x()-fa*(p2.x()-x0);    // x2-x0 is the width of triangle T
    auto p1y=p1.y()-fa*(p2.y()-p0.y());    // y2-y0 is the height of T
    auto p2x=p1.x()+fb*(p2.x()-x0);
    auto p2y=p1.y()+fb*(p2.y()-p0.y());
    c0.setX(p1x);
    c0.setY(p1y);
    c1.setX(p2x);
    c1.setY(p2y);
}


void Splines::drawShape(QPainter &painter, float mu, const std::vector<QPointF>& points)
{
    painter.setPen( Qt::black );
    for (size_t i = 0; i < points.size() - 1; i++)
    {
        const auto& p0 = points[i];
        const auto& p1 = points[i + 1];
        painter.drawLine(p0, p1);
    }

    //   Append and prepend knots and control points to close the curve
    pts.push(pts[0],pts[1],pts[2],pts[3]);
    pts.unshift(pts[n-1]);
    pts.unshift(pts[n-1]);
    for(var i=0;i<n;i+=2)
    {
        cp=cp.concat(getControlPoints(pts[i],pts[i+1],pts[i+2],pts[i+3],pts[i+4],pts[i+5],t));
    }
    cp=cp.concat(cp[0],cp[1]);
    for(var i=2;i<n+2;i+=2)
    {
        var color=HSVtoRGB(Math.floor(240*(i-2)/(n-2)),0.8,0.8);
        if(!showDetails){color="#555555"}
        ctx.strokeStyle=hexToCanvasColor(color,0.75);
        ctx.beginPath();
        ctx.moveTo(pts[i],pts[i+1]);
        ctx.bezierCurveTo(cp[2*i-2],cp[2*i-1],cp[2*i],cp[2*i+1],pts[i+2],pts[i+3]);
        ctx.stroke();
        ctx.closePath();
        if(showDetails){
           drawControlLine(ctx,pts[i],pts[i+1],cp[2*i-2],cp[2*i-1]);
           drawControlLine(ctx,pts[i+2],pts[i+3],cp[2*i],cp[2*i+1]);
        }
    }
}

void Splines::drawSpline(QPainter& painter, const QPointF& start, const QPointF& end, const QPointF& c0, const QPointF& c1)
{
    QPainterPath path;
    path.moveTo(start);
    path.cubicTo(c0, c1, end);

    painter.drawPath(path);
}

