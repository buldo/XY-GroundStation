#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#include "pico_servo.hpp"

#define KILO 1e3
#define MICRO 1e-6
#define WRAP 10000
#define FREQ 50 // PWM frequency in hertz

ServoController::ServoController()
{
    uint clockSource = CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY;
    _clockDivider = (float)frequency_count_khz(clockSource) * (float)KILO / (FREQ * WRAP);
    _usPerUnit = 1.f / (FREQ * WRAP) / MICRO;

    _min = _minUs / _usPerUnit;
    _max = _maxUs / _usPerUnit;
}

ServoController::~ServoController()
{
}

void ServoController::EnableForPin(const uint gpio)
{
    uint slice = pwm_gpio_to_slice_num(gpio);
    if (_slicesActive[slice] >= 2)
    {
        return;
    }

    gpio_set_function(gpio, GPIO_FUNC_PWM);
    
    if (_slicesActive[slice] == 0)
    {
        pwm_clear_irq(slice);
        pwm_set_irq_enabled(slice, true);

        auto config = pwm_get_default_config();
        pwm_config_set_wrap(&config, WRAP);
        pwm_config_set_clkdiv(&config, _clockDivider);
        pwm_init(slice, &config, true);
        pwm_set_chan_level(slice, gpio & 1u, 90);
    }

    ++_slicesActive[slice];
}

void ServoController::SetAngle(const uint gpio, const float angle)
{
    const uint8_t slice = pwm_gpio_to_slice_num(gpio);
    const uint8_t channel = pwm_gpio_to_channel(gpio);

    uint val = (float)angle / servoMaxAngle * (_max - _min) + _min;

    pwm_set_chan_level(slice, channel, val);
    pwm_set_enabled(slice, true);
}