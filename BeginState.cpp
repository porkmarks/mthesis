#include "BeginState.h"
#include <iostream>
#include "ShapeState.h"

BeginState::~BeginState()
{
    delete m_widget;
}


void BeginState::init(QWidget* mainWidget)
{
    m_data.reset(new StateData);

    //create a new widget to put our sliders into
    m_widget = new QWidget(mainWidget);

    //add the widget to the main widget (the main window)
    mainWidget->layout()->addWidget(m_widget);

    //m_widget->setLayout(new QVBoxLayout(m_widget));


    //construct the UIs in the widgets. This will spawn all the icons and sliders
    m_beginUi.setupUi(m_widget);

}

void BeginState::process()
{
    bool hasName = m_beginUi.lineEdit->text().count() > 0;
    m_beginUi.startButton->setEnabled(hasName);
}

StateData& BeginState::getData()
{
    return *m_data;
}

std::unique_ptr<State> BeginState::finish()
{
    if (m_beginUi.startButton->isChecked())
    {
        QString qname = m_beginUi.lineEdit->text();
        std::string name = qname.toLatin1().data();

        m_data->startTimePoint = std::chrono::system_clock::now();
        m_data->sensorDataFile.open("data/data_" + name + ".csv");
        if (!m_data->sensorDataFile)
        {
            abort();
        }

        m_data->sensorDataFile << "Timestamp"
                        << "," << "LCTR"
                        << "," << "Sharpness"
                        << "," << "Movement"
                        << "," << "Positivity"
                        << "," << "Arousal"
                        << "," << "Iteration"
                        << "," << "GSR"
                        << std::endl;


        return std::unique_ptr<State>(new ShapeState(m_data));
    }

    return nullptr;
}
