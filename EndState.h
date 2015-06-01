#pragma once

#include "State.h"

class EndState : public State
{
public:
    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();
};

