#include "EndState.h"
#include <iostream>

EndState::EndState(std::shared_ptr<StateData> data)
{
    m_data = data;
}

void EndState::init(QWidget* widget)
{

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
