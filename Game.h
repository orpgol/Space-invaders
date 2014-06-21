#ifndef GAME_H
#define GAME_H

#include <p18cxxx.h>
#include "main.h"
#include "menu.h"
#include "BMA150.h"
#include "oled.h"
#include "PushButton.h"
#include "Timer.h"
#include "mtouch.h"
#include "EEPROM.h"
#include "WDT.h"
#include "isr.h"

void game();
void Main_Timer();
void game_over(int score);
void about();

#endif