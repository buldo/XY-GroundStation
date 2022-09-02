#pragma once

class ServoController
{
private:
    uint _minUs = 500;
    uint _maxUs = 2500;
    uint _min;
    uint _max;
    float _usPerUnit = 0.f;
    float _clockDivider;
    uint _slicesActive[8] = {0};
public:
    ServoController();
    void EnableForPin(const uint gpio);
    void SetAngle(const uint gpio, const uint8_t angle);

    ~ServoController();
};