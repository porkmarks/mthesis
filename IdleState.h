#pragma once

#include "State.h"
#include <chrono>

class IdleState : public State
{
public:
    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();

private:
    std::chrono::system_clock::time_point m_start;
};

