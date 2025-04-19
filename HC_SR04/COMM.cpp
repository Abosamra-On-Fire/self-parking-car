
#include "COMM.h"

char FindPort(uint8_t Pin) {
    if (Pin <= 7) {
        return 'D';
    }else if (Pin <= 13) {
        return 'B';
    }else if (Pin <= 19) {
        return 'C';
    }else {
        return 'N';
    }
}

uint8_t FindPin(uint8_t Pin) {
    if (Pin <= 7) {
        return Pin;
    }else if (Pin<= 13) {
        return Pin - 8;
    }else if (Pin<= 19) {
        return Pin-14;
    }else {
        return -1;
    }
}



uint8_t digital_write(uint8_t Pin, bool dir) {
    char port = FindPort(Pin);
    uint8_t pin = FindPin(Pin);

    if (dir) {
        if (port == 'D') {
            PORTD |= (1 << pin);
        }else if (port == 'B') {
            PORTB |= (1 << pin);
        }else if (port == 'C') {
            PORTC |= (1 << pin);
        }
    }else {
        if (port == 'D') {
            PORTD &= ~(1 << pin);
        }else if (port == 'B') {
            PORTB &= ~(1 << pin);
        }else if (port == 'C') {
            PORTC &= ~(1 << pin);
        }
    }
}

void SetPin(uint8_t Pin,bool dir) {
    char port = FindPort(Pin);
    uint8_t pin = FindPin(Pin);

    if (dir) {
        if (port == 'D') {
            DDRD |= (1 << pin);
        }else if (port == 'B') {
            DDRB |= (1 << pin);
        }else if (port == 'C') {
            DDRC |= (1 << pin);
        }
    }else {
        if (port == 'D') {
            DDRD &= ~(1 << pin);
        }else if (port == 'B') {
            DDRB &= ~(1 << pin);
        }else if (port == 'C') {
            DDRC &= ~(1 << pin);
        }
    }
}
