#include "EndState.h"
#include <iostream>

EndState::EndState(std::shared_ptr<StateData> data)
{
    m_data = data;
}

void EndState::init(QWidget* mainWidget)
{
    //create a new widget to put our sliders into
    m_widget = new QWidget(mainWidget);

    //add the widget to the main widget (the main window)
    mainWidget->layout()->addWidget(m_widget);

    //m_widget->setLayout(new QVBoxLayout(m_widget));


    //construct the UIs in the widgets. This will spawn all the icons and sliders
    m_endUi.setupUi(m_widget);

}

void EndState::process()
{
}

std::unique_ptr<State> EndState::finish()
{
    return nullptr;
}

StateData& EndState::getData()
{
    return *m_data;
}
