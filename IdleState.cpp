#include "IdleState.h"
#include "ShapeState.h"
#include <iostream>
#include <QLayout>

const std::chrono::seconds DURATION(1);

IdleState::IdleState(std::shared_ptr<StateData> data)
{
    m_data = data;
}

IdleState::~IdleState()
{
    delete m_widget;
}

void IdleState::init(QWidget* mainWidget)
{
    m_start = std::chrono::system_clock::now();

    //create a new widget to put our sliders into
    m_widget = new QWidget(mainWidget);

    //add the widget to the main widget (the main window)
    mainWidget->layout()->addWidget(m_widget);

    m_widget->setStyleSheet("background-color:black;");
    m_widget->show();

}

void IdleState::process()
{
}

std::unique_ptr<State> IdleState::finish()
{
    auto now = std::chrono::system_clock::now();
    if (now - m_start >= DURATION)
    {
        return std::unique_ptr<State>(new ShapeState(m_data));
    }
    else
    {
        return nullptr;
    }

}

