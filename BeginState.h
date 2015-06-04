#pragma once

#include "State.h"
#include <QPushButton>

#include "ui_ArousalWidget.h"
#include "ui_PositivityWidget.h"
#include "ui_BeginWidget.h"

class BeginState : public State
{
public:
    ~BeginState();
    void init(QWidget* widget);
    void process();
    std::unique_ptr<State> finish();

private:
    std::shared_ptr<StateData> m_data;


    QWidget* m_widget;
    Ui::BeginWidget m_beginUi;



};

