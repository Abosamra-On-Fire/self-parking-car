#include "HC_SR04.h"

HC_SR04 ultrasonic(10, 11);

void setup() {
    Serial.begin(9600);
    ultrasonic.begin();
}

void loop() {
    float distance = ultrasonic.getDistanceCM();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    delay(500); 
}