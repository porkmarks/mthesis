#include "EndState.h"
#include <iostream>

void EndState::init(QWidget* widget)
{

}

void EndState::process()
{
    std::cout << "EndofBussines" << std::endl;
}

std::unique_ptr<State> EndState::finish()
{
    return nullptr;
}

