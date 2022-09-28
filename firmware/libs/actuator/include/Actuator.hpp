#pragma once

#include "pico/stdlib.h"
#include "pico_servo.hpp"

class Actuator
{
private:
    bool isInManualMode;
    
    /* Antenna positioning START */
    int32_t theta1;
    int32_t theta2;
    uint32_t az;
    uint32_t el;
    /* Antenna positioning END */

    /* Servo controll START */
    ServoController *servoController;
    int servo1Pin; 
    int servo2Pin;
    /* Servo controll END */
public:
    Actuator(ServoController *servoController, int servo1Pin, int servo2Pin);
    ~Actuator();
    void SetManualMode(bool isManualModeOn);
    void SetPosition(int32_t az, int32_t el);
    uint32_t GetAz();
    uint32_t GetEl();
};
