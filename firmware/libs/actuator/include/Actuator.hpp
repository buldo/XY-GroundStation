#pragma once

#include "pico/stdlib.h"
#include "pico_servo.hpp"

class Actuator
{
private:
    bool isInManualMode_;
    
    /* Antenna positioning START */
    int32_t theta1_;
    int32_t theta2_;
    uint32_t az_;
    uint32_t el_;
    /* Antenna positioning END */

    /* Servo controll START */
    ServoController *servoController_;
    int servo1Pin_; 
    int servo2Pin_;
    /* Servo controll END */
public:
    Actuator(ServoController *servoController, int servo1Pin, int servo2Pin);
    ~Actuator();
    void SetManualMode(bool isManualModeOn);
    void SetPosition(int32_t az, int32_t el);
    void SetServoPosition(uint32_t theta1, uint32_t theta2);
    uint32_t GetAz();
    uint32_t GetEl();
    uint32_t GetTheta1();
    uint32_t GetTheta2();
    void applyPosition();
};
