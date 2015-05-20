#ifndef SPLINES_H
#define SPLINES_H

#include <QDialog>
#include <QtGui>
#include <QtCore>

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

    Ui::Splines *ui;
    float m_ltcr = 0;
    float m_curviness = 0.5f;
    std::vector<Point> m_points;
};

#endif // SPLINES_H
