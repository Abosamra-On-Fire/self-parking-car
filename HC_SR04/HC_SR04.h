#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>  
#include "COMM.h"

class HC_SR04 {
public:
    HC_SR04(uint8_t triggerPin, uint8_t echoPin);
    void begin();
    float getDistanceCM();
    unsigned long getDuration();
    
private:
    uint8_t _triggerPin;
    uint8_t _echoPin;
    unsigned long _duration;
    float _distanceCM;
    void _sendPulse();
};

#endif