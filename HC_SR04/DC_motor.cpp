#include "DC_motor.h"
#include "COMM.h"
#include "soc/ledc_struct.h"
#include "soc/ledc_reg.h"

DCMotor::DCMotor(uint8_t in1, uint8_t in2, uint8_t pwm) :
    in1_pin(in1), in2_pin(in2), pwm_pin(pwm),
    current_speed(0), current_direction(MOTOR_STOP) {}

void DCMotor::init() {
    configureGPIO();
    configurePWM();
    stop();
}

void DCMotor::configureGPIO() {
    set_pin(in1_pin, true);
    set_pin(in2_pin, true);
    digital_write(in1_pin, false);
    digital_write(in2_pin, false);
    set_pin(pwm_pin, true);
}

void DCMotor::configurePWM() {
    // Assuming using LEDC_HIGH_SPEED_MODE and channel 0
    // Configure LEDC timer0
    LEDC.timer_group[0].timer[0].conf.div_num = 80; // 1 MHz base clock (80MHz/80)
    LEDC.timer_group[0].timer[0].conf.duty_resolution = 0x03; // 10-bit resolution
    LEDC.timer_group[0].timer[0].conf.clk_en = 1;
    LEDC.timer_group[0].timer[0].conf.tick_sel = 1;
    LEDC.timer_group[0].timer[0].conf.low_speed_update = 1;
    LEDC.timer_group[0].timer[0].conf.pause = 0;

    // Channel 0 config for PWM output
    LEDC.channel_group[0].channel[0].conf0.timer_sel = 0;
    LEDC.channel_group[0].channel[0].conf0.sig_out_en = 1;
    LEDC.channel_group[0].channel[0].conf0.idle_lv = 0;
    LEDC.channel_group[0].channel[0].conf0.low_speed_update = 1;

    // Assign GPIO to channel 0
    uint32_t reg = GPIO_PIN_MUX_REG[pwm_pin];
    REG_WRITE(reg, (REG_READ(reg) & ~(FUN_DRV | MCU_SEL | FUN_IE)) | FUNC_GPIO);
    gpio_matrix_out(pwm_pin, LEDC_HS_SIG_OUT0_IDX, 0, 0);

    setPWMDuty(0);
}

void DCMotor::set(uint8_t speed, MotorDirection direction) {
    setSpeed(speed);
    setDirection(direction);
}

void DCMotor::setSpeed(uint8_t speed) {
    current_speed = (speed > 100) ? 100 : speed;
    setPWMDuty(current_speed);
}

void DCMotor::setDirection(MotorDirection direction) {
    current_direction = direction;

    switch (direction) {
        case MOTOR_FORWARD:
            digital_write(in1_pin, true);
            digital_write(in2_pin, false);
            break;
        case MOTOR_BACKWARD:
            digital_write(in1_pin, false);
            digital_write(in2_pin, true);
            break;
        case MOTOR_BRAKE:
            digital_write(in1_pin, true);
            digital_write(in2_pin, true);
            setPWMDuty(100);
            break;
        case MOTOR_STOP:
        default:
            digital_write(in1_pin, false);
            digital_write(in2_pin, false);
            setPWMDuty(0);
            break;
    }
}

void DCMotor::stop() {
    setDirection(MOTOR_STOP);
}

void DCMotor::brake() {
    setDirection(MOTOR_BRAKE);
}

void DCMotor::setPWMDuty(uint8_t duty) {
    uint32_t duty_val = (duty * 1023) / 100;

    LEDC.channel_group[0].channel[0].duty.duty = duty_val << 4;
    LEDC.channel_group[0].channel[0].conf1.duty_start = 1;
}