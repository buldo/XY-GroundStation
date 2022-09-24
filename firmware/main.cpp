#include <stdio.h>
#include "pico/stdlib.h"

#include "ServoState.hpp"
#include "UserInterface.hpp"
#include "board_startup.hpp"
#include "Actuator.hpp"

int main() {
    boardStartup();
    
    Actuator actuator{};
    UserInterface interface(&actuator);
    interface.Init();
    // setup_default_uart();
    printf("Hello, world!\n");
    while(true){}
    return 0;
}