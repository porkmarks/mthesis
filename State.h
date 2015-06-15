#pragma once

#include <memory>
#include <QtWidgets/QWidget>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>


enum class Range
{
    LOW,
    LOWMEDIUM,
    MEDIUMHIGH,
    HIGH
};

struct ShapeDescription
{
    Range ltcrRange;
    Range sharpnessRange;
    Range movementRange;
};

struct SensorData
{
    std::string value;
    std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();
};


struct StateData
{
    std::chrono::system_clock::time_point startTimePoint;
    int iterationCount = 0;
    std::ofstream sensorDataFile;
    std::ofstream assesmentDataFile;

    ShapeDescription shapeDescription;

    std::vector<SensorData> sensorData;

    int positivity = 0;
    int arousal = 0;
};



class State
{
public:
    virtual ~State() {}


    //init is called only once, when the state is entered
    virtual void init(QWidget* widget) = 0;

    //process is called per frame until finish returns a non-null state
    virtual void process() = 0;

    //finish is called per frame until it returns a non-null state
    virtual std::unique_ptr<State> finish() = 0;

    virtual StateData& getData() = 0;
};

