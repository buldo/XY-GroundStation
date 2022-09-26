#include <stdio.h>
#include "pico/stdlib.h"

#include "UserInterface.hpp"
#include "board_startup.hpp"
#include "Actuator.hpp"
#include "pico_servo.hpp"

int main() {
    boardStartup();
    
    ServoController servoController{};
    Actuator actuator(&servoController, SERVO1_PIN, SERVO2_PIN);
    UserInterface interface(&actuator);
    interface.Init();
    // setup_default_uart();
    printf("Hello, world!\n");
    while(true){}
    return 0;
}