#include "Actuator.hpp"

#include <cmath>

Actuator::Actuator(/* args */)
{
}

Actuator::~Actuator()
{
}
void Actuator::SetManualMode(bool isManualModeOn)
{
    isInManualMode = isManualModeOn;
}