
#ifndef COMM_h
#define COMM_h

#include <stdint.h>
#include <stdbool.h>

void digital_write(uint8_t pin, bool state);
bool digital_read(uint8_t pin);
void set_pin(uint8_t pin, bool dir);


#endif