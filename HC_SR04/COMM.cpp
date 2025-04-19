
#include <COMM.h>

#define GPIO_OUT_W1TS_REG  (*((volatile uint32_t *)0x3FF44008)) 
#define GPIO_OUT_W1TC_REG  (*((volatile uint32_t *)0x3FF4400C)) 
#define GPIO_ENABLE_W1TS_REG (*((volatile uint32_t *)0x3FF44024))
#define GPIO_ENABLE_W1TC_REG (*((volatile uint32_t *)0x3FF44028))
#define GPIO_IN_REG        (*((volatile uint32_t *)0x3FF4403C))
#define GPIO_IN1_REG       (*((volatile uint32_t *)0x3FF44040))

#define GPIO_OUT1_W1TS_REG (*((volatile uint32_t *)0x3FF44014))
#define GPIO_OUT1_W1TC_REG (*((volatile uint32_t *)0x3FF44018))
#define GPIO_ENABLE1_W1TS_REG (*((volatile uint32_t *)0x3FF44030))
#define GPIO_ENABLE1_W1TC_REG (*((volatile uint32_t *)0x3FF44034))


void set_pin(uint8_t pin, bool dir) {
    if (pin > 39) return;

    if (pin < 32) {
        if (dir) {
            GPIO_ENABLE_W1TS_REG = (1 << pin);
        }
        else {
            GPIO_ENABLE_W1TC_REG = (1 << pin);
        }
    }
    else {
        if (dir) {
            GPIO_ENABLE1_W1TS_REG = (1 << (pin - 32));
        }
        else {
            GPIO_ENABLE1_W1TC_REG = (1 << (pin - 32));
        }
    }
}

void digital_write(uint8_t pin, bool state) {
    if (pin > 39) return;
    if (pin < 32) {
        if (state) {
            GPIO_OUT_W1TS_REG = (1 << pin);
        }
        else {
            GPIO_OUT_W1TC_REG = (1 << pin);
        }
    }
    else {
        if (state) {
            GPIO_OUT1_W1TS_REG = (1 << (pin - 32));
        }
        else {
            GPIO_OUT1_W1TC_REG = (1 << (pin - 32));
        }
    }
}

bool digital_read(uint8_t pin) {
    if (pin > 39) return;
    if (pin < 32) {
        return (GPIO_IN_REG >> pin) & 0x1;
    }
    else {
        return (GPIO_IN1_REG >> (pin - 32)) & 0x1;
    }
}