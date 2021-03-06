# MPLAB IDE generated this makefile for use with GNU make.
# Project: Lab0.mcp
# Date: Tue Feb 11 18:58:26 2014

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

Lab0.cof : main.o oled.o PushButton.o Timer.o WDT.o BMA150.o mtouch.o isr.o menu.o ADC.o EEPROM.o Game.o
	$(LD) /p18F46J50 "main.o" "oled.o" "PushButton.o" "Timer.o" "WDT.o" "BMA150.o" "mtouch.o" "isr.o" "menu.o" "ADC.o" "EEPROM.o" "Game.o" /u_CRUNTIME /u_DEBUG /m"Lab0.map" /w /o"Lab0.cof"

main.o : main.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdio.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdlib.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/string.h BMA150.h oled.h Timer.h mtouch.h main.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h main.h menu.h Compiler.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdarg.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stddef.h GenericTypeDefs.h PushButton.h Game.h
	$(CC) -p=18F46J50 "main.c" -fo="main.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

oled.o : oled.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdio.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdlib.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/string.h oled.h oled.c GenericTypeDefs.h Compiler.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdarg.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stddef.h
	$(CC) -p=18F46J50 "oled.c" -fo="oled.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

PushButton.o : PushButton.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h PushButton.h
	$(CC) -p=18F46J50 "PushButton.c" -fo="PushButton.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

Timer.o : Timer.c Timer.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdio.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdlib.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/string.h oled.h BMA150.h mtouch.h Timer.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h Compiler.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdarg.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stddef.h GenericTypeDefs.h PushButton.h isr.h Game.h main.h menu.h
	$(CC) -p=18F46J50 "Timer.c" -fo="Timer.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

WDT.o : WDT.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdio.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdlib.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/string.h oled.h BMA150.h Timer.h mtouch.h WDT.c WDT.h main.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h Compiler.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdarg.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stddef.h GenericTypeDefs.h PushButton.h isr.h Game.h menu.h
	$(CC) -p=18F46J50 "WDT.c" -fo="WDT.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

BMA150.o : BMA150.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdio.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdlib.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/string.h BMA150.h oled.h Timer.h mtouch.h BMA150.c Compiler.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdarg.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stddef.h GenericTypeDefs.h isr.h Game.h main.h menu.h PushButton.h
	$(CC) -p=18F46J50 "BMA150.c" -fo="BMA150.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

mtouch.o : mtouch.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdio.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdlib.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/string.h mtouch.h oled.h BMA150.h Timer.h mtouch.c Compiler.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdarg.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stddef.h GenericTypeDefs.h isr.h Game.h main.h menu.h PushButton.h
	$(CC) -p=18F46J50 "mtouch.c" -fo="mtouch.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

isr.o : isr.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdio.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdlib.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/string.h BMA150.h oled.h Timer.h mtouch.h isr.c WDT.h main.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h isr.h Game.h menu.h Compiler.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdarg.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stddef.h GenericTypeDefs.h PushButton.h
	$(CC) -p=18F46J50 "isr.c" -fo="isr.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

menu.o : menu.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdio.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdlib.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/string.h oled.h mtouch.h BMA150.h Timer.h ADC.h menu.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h Menu.h Compiler.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdarg.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stddef.h GenericTypeDefs.h WDT.h main.h
	$(CC) -p=18F46J50 "menu.c" -fo="menu.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

ADC.o : ADC.c ADC.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdio.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdlib.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/string.h oled.h mtouch.h BMA150.h Timer.h ADC.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h Compiler.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdarg.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stddef.h GenericTypeDefs.h isr.h Game.h main.h menu.h PushButton.h
	$(CC) -p=18F46J50 "ADC.c" -fo="ADC.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

EEPROM.o : EEPROM.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdio.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdlib.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/string.h EEPROM.h EEPROM.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h Compiler.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdarg.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stddef.h GenericTypeDefs.h
	$(CC) -p=18F46J50 "EEPROM.c" -fo="EEPROM.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

Game.o : Game.c ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdio.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdlib.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/string.h BMA150.h oled.h Timer.h mtouch.h Game.c Game.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18cxxx.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/p18f46j50.h main.h menu.h Compiler.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stdarg.h ../../../../Microchip\ Starter\ Kits/PIC18F\ Starter\ Kit\ 1/MPLAB\ C18/h/stddef.h GenericTypeDefs.h PushButton.h
	$(CC) -p=18F46J50 "Game.c" -fo="Game.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "main.o" "oled.o" "PushButton.o" "Timer.o" "WDT.o" "BMA150.o" "mtouch.o" "isr.o" "menu.o" "ADC.o" "EEPROM.o" "Game.o" "Lab0.cof" "Lab0.hex" "Lab0.map"

