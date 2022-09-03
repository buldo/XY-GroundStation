#pragma once

#include "hardware/spi.h"

#define DISPLAY_SPI_PORT spi1

const int EPD_RST_PIN = 12;
const int EPD_DC_PIN = 8;
const int EPD_CS_PIN = 9;
const int EPD_BL_PIN = 13;
const int EPD_CLK_PIN = 10;
const int EPD_MOSI_PIN = 11;
