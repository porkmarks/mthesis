#pragma once

#include "State.h"

class AssesmentState : public State
{
public:
    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();
};

