#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include <stdint.h>

enum MotorDirection {
    MOTOR_STOP,
    MOTOR_FORWARD,
    MOTOR_BACKWARD,
    MOTOR_BRAKE
};

class DCMotor {
public:
    DCMotor(uint8_t in1_pin, uint8_t in2_pin, uint8_t pwm_pin);
    void init();
    void set(uint8_t speed, MotorDirection direction);
    void setSpeed(uint8_t speed);
    void setDirection(MotorDirection direction);
    void stop();
    void brake();

private:
    uint8_t in1_pin;
    uint8_t in2_pin;
    uint8_t pwm_pin;
    uint8_t current_speed;
    MotorDirection current_direction;

    void configureGPIO();
    void configurePWM();
    void setPWMDuty(uint8_t duty);
};

#endif
