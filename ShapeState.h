#pragma once

#include "State.h"
#include <chrono>
#include <vector>

class ShapeState : public State
{
public:
    ShapeState(std::shared_ptr<StateData> data);

    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();

private:
    std::shared_ptr<StateData> m_data;

    QWidget* m_widget = nullptr;

    std::chrono::system_clock::time_point m_start;

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
    Clock::time_point m_last_tp = Clock::now();


    struct Params
    {
        float sharpness = 0;
        float ltcr = 0;
        float movement = 0;
    } m_params;

    enum class Range
    {
        LOW,
        LOWMEDIUM,
        MEDIUMHIGH,
        HIGH
    };

    struct Cell
    {
        Range ltcrRange;
        Range sharpnessRange;
        Range movementRange;
    };

    std::pair<float, float> getMinMaxFromRange(Range range) const;
    void initParamsFromCell(const Cell& cell);

    static std::vector<Cell> s_cells;
};

