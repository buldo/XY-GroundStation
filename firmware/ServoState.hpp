#pragma once

#include <cmath>

class ServoState
{
private:
    int32_t _theta1;
    int32_t _theta2;
    uint32_t _az;
    uint32_t _el;
public:
    int32_t GetTheta1()
    {
        return _theta1;
    }

    int32_t GetTheta2()
    {
        return _theta2;
    }

    uint32_t GetAz()
    {
        return _az;
    }

    uint32_t GetEl()
    {
        return _el;
    }

    void SetThetaPosition(uint32_t theta1, uint32_t theta2)
    {
        _theta1 = theta1;
        _theta2 = theta2;
    }

    void SetTheta1(uint32_t theta1)
    {
        _theta1 = theta1;
    }

    void SetTheta2(uint32_t theta2)
    {
        _theta2 = theta2;
    }

    void SetPosition(uint32_t az, uint32_t el)
    {
        _az = az;
        _el = el;

        auto azRad = az * (M_PI / 180);
        auto elRad = el * (M_PI / 180);

        auto theta1Rad = atanl( (cosl(azRad) * cosl(elRad)) / (sinl(elRad)) );
        _theta1 = theta1Rad * 180 / M_PI + 90;

        auto theta2Rad = asinl( sinl(azRad) * cosl(elRad) );
        _theta2 = (theta2Rad ) * 180 / M_PI + 90;
    }
};