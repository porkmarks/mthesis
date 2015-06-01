#pragma once

#include "State.h"
#include <chrono>

class ShapeState : public State
{
public:
    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();

private:
    QWidget* m_widget = nullptr;
    float m_ltcr = 0;//0..1
    float m_sharpness = 0;//0..1
    float m_speed = 0; //0..1

    struct Point
    {
        QPointF point;
        float t;
    };

    std::vector<Point> generatePoints(size_t count, float radius, float sharpness);
    std::vector<Point> assignLTC(const std::vector<Point>& points, float ltcr);

    void getControlPoints(QPointF p0, QPointF p1, QPointF p2, float t, QPointF& c0, QPointF& c1);
    QImage floodFill(const QImage& img, const QPoint &pos, const QRgb &newColor);

    QImage buildShape(const std::vector<Point>& _points);

    float m_curviness = 0.5f;
    std::vector<Point> m_points;
    QImage m_shape;

    QPointF m_target;
    QPointF m_position;

    typedef std::chrono::high_resolution_clock Clock;
    Clock::time_point m_last_target_tp = Clock::now();
};

