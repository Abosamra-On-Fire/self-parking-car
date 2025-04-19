
#ifndef COMM_h
#define COMM_h

#include <avr/io.h>


char FindPort(uint8_t Pin);
uint8_t FindPin(uint8_t Pin);
uint8_t digital_write(uint8_t Pin, bool dir);
void SetPin(uint8_t Pin, bool dir);


#endif