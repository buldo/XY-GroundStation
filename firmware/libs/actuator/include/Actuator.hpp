#pragma once

class Actuator
{
private:
    bool isInManualMode;
    
    /* Antenna positioning START */
    int32_t _theta1;
    int32_t _theta2;
    uint32_t _az;
    uint32_t _el;
    /* Antenna positioning END */
public:
    Actuator(/* args */);
    ~Actuator();
    void SetManualMode(bool isManualModeOn);
    void SetPosition(uint32_t az, uint32_t el);
};
