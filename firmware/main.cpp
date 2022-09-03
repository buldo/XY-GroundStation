#include <stdio.h>
#include "pico/stdlib.h"

#include "ServoState.hpp"
#include "user_interface.hpp"
#include "board_startup.hpp"

int main() {
    boardStartup();
    UserInterface interface{};
    interface.Init();
    // setup_default_uart();
    printf("Hello, world!\n");
    return 0;
}