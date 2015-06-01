#pragma once

#include "State.h"
#include "IdleState.h"
#include "EndState.h"

class AssesmentState : public State
{
public:
    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();
private:
    std::chrono::system_clock::time_point m_start;
    static int s_counter;

};

