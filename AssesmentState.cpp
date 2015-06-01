#include "AssesmentState.h"
#include <iostream>

const std::chrono::seconds ASSESMENT_DURATION(3);

int AssesmentState::s_counter = 0;

void AssesmentState::init(QWidget* widget)
{
    m_start = std::chrono::system_clock::now();
    s_counter++;
}

void AssesmentState::process()
{
    std::cout << "Assesment process " << s_counter  << std::endl;
}

std::unique_ptr<State> AssesmentState::finish()
{
    auto now = std::chrono::system_clock::now();

    if (s_counter <= 3)
    {
        if (now - m_start >= ASSESMENT_DURATION)
        {
            return std::unique_ptr<State>(new IdleState);
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return std::unique_ptr<State>(new EndState);
    }


}
