#include "AssesmentState.h"
#include <iostream>

void AssesmentState::init(QWidget* widget)
{
    std::cout << "Assesment init" << std::endl;
}

void AssesmentState::process()
{
    std::cout << "Assesment process" << std::endl;
}

std::unique_ptr<State> AssesmentState::finish()
{
    std::cout << "Assesment finish" << std::endl;
    return nullptr;
}
