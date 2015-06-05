#pragma once

#include <memory>
#include <QtWidgets/QWidget>
#include <iostream>
#include <fstream>
#include <chrono>


struct StateData
{
    std::chrono::system_clock::time_point startTimePoint;
    int iterationCount = 0;
    std::ofstream sensorDataFile;
    std::ofstream shapeDataFile;
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

