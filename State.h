#pragma once

#include <memory>
#include <QtWidgets/QWidget>

class State
{
public:
    //init is called only once, when the state is entered
    virtual void init(QWidget* widget) = 0;

    //process is called per frame until finish returns a non-null state
    virtual void process() = 0;

    //finish is called per frame until it returns a non-null state
    virtual std::unique_ptr<State> finish() = 0;
};

