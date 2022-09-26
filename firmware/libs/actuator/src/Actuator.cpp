#include "Actuator.hpp"

#include <cmath>

Actuator::Actuator(ServoController *servoController, int servo1Pin, int servo2Pin)
{
    this->servoController = servoController;
    this->servo1Pin = servo1Pin;
    this->servo2Pin = servo2Pin;
}

Actuator::~Actuator()
{
}

void Actuator::SetManualMode(bool isManualModeOn)
{
    isInManualMode = isManualModeOn;
}

uint32_t Actuator::GetAz()
{
    return az;
}

uint32_t Actuator::GetEl()
{
    return el;
}

void Actuator::SetPosition(uint32_t az, uint32_t el)
{
        if(el < 0)
        {
            el = 0;
        }

        if(el > 180)
        {
            el = 180;
        }

        if(az < 0)
        {
            az = 360 + az;
        }

        if(az > 360)
        {
            az = 360 - az;
        }

        this->az = az;
        this->el = el;

        auto azRad = az * (M_PI / 180);
        auto elRad = el * (M_PI / 180);

        auto theta1Rad = atanl( (cosl(azRad) * cosl(elRad)) / (sinl(elRad)) );
        theta1 = theta1Rad * 180 / M_PI + 90;

        auto theta2Rad = asinl( sinl(azRad) * cosl(elRad) );
        theta2 = (theta2Rad ) * 180 / M_PI + 90;
}