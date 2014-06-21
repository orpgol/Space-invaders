#ifndef EEPROM_H
#define EEPROM_H
#include <p18cxxx.h>
#include "Compiler.h"
#include "GenericTypeDefs.h"


void RomRead(unsigned short int adress, BYTE* data, int len);

void RomWrite(unsigned short int adress, BYTE* data, int len);

void RomDelete(unsigned short int adress);

#endif