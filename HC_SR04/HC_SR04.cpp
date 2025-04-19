#include "HC_SR04.h"

HC_SR04::HC_SR04(uint8_t triggerPin, uint8_t echoPin) {
    _triggerPin = triggerPin;
    _echoPin = echoPin;
}

void HC_SR04::begin() {
    SetPin(_triggerPin, 1);
    SetPin(_echoPin, 0);
    digital_write(_triggerPin, 0);
}

void HC_SR04::_sendPulse() {
    
    digital_write(_triggerPin, 0);
    delay(2);
    
    
    digital_write(_triggerPin, 1);
    delay(10);
    digital_write(_triggerPin, 0);
}

unsigned long HC_SR04::getDuration() {
    _sendPulse();
    _duration = pulseIn(_echoPin, HIGH);
    return _duration;
}

float HC_SR04::getDistanceCM() {
    _duration = getDuration();
    
    
    _distanceCM = _duration * 0.0343 / 2;
    return _distanceCM;
}