#pragma once

#include "State.h"
#include "IdleState.h"
#include "EndState.h"
#include <QPushButton>

#include "ui_ArousalWidget.h"
#include "ui_PositivityWidget.h"

class AssesmentState : public State
{
public:
    ~AssesmentState();
    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();

private:

    static int s_counter;

    Ui::ArousalWidget m_arousalUi;
    Ui::PositivityWidget m_positivityUi;
    QWidget* m_widget;
    QPushButton* m_button;
    bool m_wasArousalPressed = false;
    bool m_wasPositivityPressed = false;


};

