#include "Actuator.hpp"

#include <cmath>

Actuator::Actuator(ServoController *servoController, int servo1Pin, int servo2Pin)
{
    servoController_ = servoController;
    servo1Pin_ = servo1Pin;
    servo2Pin_ = servo2Pin;
    servoController_->EnableForPin(servo1Pin);
    servoController_->EnableForPin(servo2Pin);
    SetPosition(0,90);
}

Actuator::~Actuator()
{
}

void Actuator::SetManualMode(bool isManualModeOn)
{
    isInManualMode_ = isManualModeOn;
}

uint32_t Actuator::GetAz()
{
    return az_;
}

uint32_t Actuator::GetEl()
{
    return el_;
}

uint32_t Actuator::GetTheta1()
{
    return theta1_;
}

uint32_t Actuator::GetTheta2()
{
    return theta2_;
}

void Actuator::SetServoPosition(uint32_t theta1, uint32_t theta2)
{
    theta1_ = theta1;
    theta2_ = theta2;
    applyPosition();
}

void Actuator::SetPosition(int32_t az, int32_t el)
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

        this->az_ = az;
        this->el_ = el;

        auto azRad = az * (M_PI / 180);
        auto elRad = el * (M_PI / 180);

        auto theta1Rad = atanl( (cosl(azRad) * cosl(elRad)) / (sinl(elRad)) );
        theta1_ = theta1Rad * 180 / M_PI + 90;

        auto theta2Rad = asinl( sinl(azRad) * cosl(elRad) );
        theta2_ = (theta2Rad ) * 180 / M_PI + 90;

        applyPosition();
}

void Actuator::applyPosition()
{
    servoController_->SetAngle(servo1Pin_, theta2_);
    servoController_->SetAngle(servo2Pin_, theta1_);
}