#pragma once

#include "State.h"

class IdleState : public State
{
public:
    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();
};

