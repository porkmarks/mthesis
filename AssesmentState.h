#pragma once

#include "State.h"
#include "IdleState.h"
#include <QPushButton>

#include "ui_ArousalWidget.h"
#include "ui_PositivityWidget.h"

class AssesmentState : public State
{
public:
    AssesmentState(std::shared_ptr<StateData> data);

    ~AssesmentState();
    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();

    StateData& getData();


private:

    std::shared_ptr<StateData> m_data;

    Ui::ArousalWidget m_arousalUi;
    Ui::PositivityWidget m_positivityUi;
    QWidget* m_widget;
    QPushButton* m_button;
    bool m_wasArousalPressed = false;
    bool m_wasPositivityPressed = false;


};

