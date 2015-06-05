#pragma once

#include "State.h"
#include <chrono>

class IdleState : public State
{
public:
    IdleState(std::shared_ptr<StateData> data);


    ~IdleState();

    void init(QWidget* mainWidget);
    void process();
    std::unique_ptr<State> finish();

    StateData& getData();


private:
    std::shared_ptr<StateData> m_data;
    QWidget* m_widget;

    std::chrono::system_clock::time_point m_start;
};

