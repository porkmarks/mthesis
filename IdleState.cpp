#include "IdleState.h"
#include "ShapeState.h"
#include <iostream>
#include <QLayout>

const std::chrono::seconds DURATION(5);

IdleState::IdleState(std::shared_ptr<StateData> data)
{
    m_data = data;
}

IdleState::~IdleState()
{
    delete m_widget;
}


class unique_pig
{
    unique_pig(int* value)
    {
        m_value = value;
    }
    ~unique_pig()
    {
        delete m_value;
    }
private:
    int* m_value = nullptr;
};


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
        //dump all the sensor data to the file
        StateData& stateData = getData();
        for (SensorData data: stateData.sensorData)
        {
            //this data was not filled yet so stop here
            if (data.value.empty())
            {
                break;
            }

            auto d = data.timestamp - stateData.startTimePoint;
            auto seconds = std::chrono::duration_cast<std::chrono::duration<float>>(d);
            stateData.sensorDataFile << seconds.count()
                            << "," << static_cast<int>(stateData.shapeDescription.ltcrRange)
                            << "," << static_cast<int>(stateData.shapeDescription.sharpnessRange)
                            << "," << static_cast<int>(stateData.shapeDescription.movementRange)
                            << "," << stateData.positivity
                            << "," << stateData.arousal
                            << "," << stateData.iterationCount
                            << "," << data.value
                            << std::endl;
        }

        stateData.sensorData.clear();

        return std::unique_ptr<State>(new ShapeState(m_data));
    }
    else
    {
        return nullptr;
    }

}

StateData& IdleState::getData()
{
    return *m_data;
}


