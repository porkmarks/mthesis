#include "IdleState.h"
#include "ShapeState.h"
#include <iostream>

const std::chrono::seconds DURATION(1);

void IdleState::init(QWidget* widget)
{
    m_start = std::chrono::system_clock::now();
}

void IdleState::process()
{
    std::cout << "Idle process" << std::endl;
}

std::unique_ptr<State> IdleState::finish()
{
    auto now = std::chrono::system_clock::now();
    if (now - m_start >= DURATION)
    {
        return std::unique_ptr<State>(new ShapeState);
    }
    else
    {
        return nullptr;
    }

}

