#pragma once

#include "State.h"
#include "ui_EndState.h"

class EndState : public State
{
public:
    EndState(std::shared_ptr<StateData> data);

    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();

    StateData& getData();

private:
    std::shared_ptr<StateData> m_data;
    QWidget* m_widget;
    Ui::EndState m_endUi;

};

