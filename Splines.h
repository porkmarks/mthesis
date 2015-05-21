#ifndef SPLINES_H
#define SPLINES_H

#include <QDialog>
#include <QtGui>
#include <QtCore>

#include <chrono>

namespace Ui {
class Splines;
}

class Splines : public QDialog
{
public:
    explicit Splines(QWidget *parent = 0);
    ~Splines();

private:
    void paintEvent(QPaintEvent *e);

    struct Point
    {
        QPointF point;
        float t;
    };

    std::vector<Point> generatePoints(size_t count, float radius);
    std::vector<Point> assignLTC(const std::vector<Point>& points, float ltcr);

    void getControlPoints(QPointF p0, QPointF p1, QPointF p2, float t, QPointF& c0, QPointF& c1);
    QImage floodFill(const QImage& img, const QPoint &pos, const QRgb &newColor);

    QImage buildShape(const std::vector<Point>& _points);

    Ui::Splines *m_ui;
    float m_ltcr = 0;
    float m_curviness = 0.5f;
    float m_speed = 0.f;
    std::vector<Point> m_points;
    QImage m_shape;

    QPointF m_target;
    QPointF m_position;

    typedef std::chrono::high_resolution_clock Clock;

    Clock::time_point m_last_target_tp = Clock::now();
};

#endif // SPLINES_H
