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
    Ui::Splines *ui;
    float m_curviness = 0;

protected:
    void paintEvent(QPaintEvent *e);
    void drawShape(QPainter &painter, float mu, const std::vector<QPointF>& points);
    void drawSpline(QPainter& painter, const QPointF& start, const QPointF& end, const QPointF& c0, const QPointF& c1);

};

#endif // SPLINES_H
