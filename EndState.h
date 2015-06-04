#pragma once

#include "State.h"

class EndState : public State
{
public:
    EndState(std::shared_ptr<StateData> data);

    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();
private:
    std::shared_ptr<StateData> m_data;

};

