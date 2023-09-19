
#pragma once

#include <Arduino.h>
#include "Wire.h"

#define LCD_ADRS 0x3E
#define LINE_WIDTH 16

class LCD {
public:
    bool begin();

    void setLine1(const char* str);
    void setLine2(const char* str);

    void show();
    void update();

private:
    char line1[LINE_WIDTH + 2];
    char line2[LINE_WIDTH + 2];

    int update_sequence;
    unsigned long update_wait_millis;

    void writeData(byte t_data);
    void writeCommand(byte t_command);
};
