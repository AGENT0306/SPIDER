#include "../include/spdServo.h"

SpiderServo::SpiderServo() : channel(-1), PWMval(PWM_CENTER), trim(0), pwm(nullptr), ang(0.0) {
}

SpiderServo::SpiderServo(int ch, Adafruit_PWMServoDriver* p)
    : channel(ch), PWMval(PWM_CENTER), trim(0), pwm(p), ang(0.0) {
}

int SpiderServo::getChannel() const {
    return channel;
}

int SpiderServo::getPWM() const {
    return PWMval;
}

double SpiderServo::getAngle() const {
    return ang;
}

int SpiderServo::clampPWM(int p) const {
    if (p < PWM_MIN) return PWM_MIN;
    if (p > PWM_MAX) return PWM_MAX;
    return p;
}

void SpiderServo::setPWM(int p) {
    int oldPWM = PWMval;
    PWMval = p;
    ang = convertPWM(PWMval);

    if (pwm == nullptr) return;

    int targetHW = clampPWM(PWMval + trim);
    int startHW = clampPWM(oldPWM + trim);

    if (startHW < targetHW) {
        for (int i = startHW; i <= targetHW; i++) {
            pwm->setPWM(channel, 0, i);
            delay(SMOOTH_DELAY_MS);
        }
    } else if (startHW > targetHW) {
        for (int i = startHW; i >= targetHW; i--) {
            pwm->setPWM(channel, 0, i);
            delay(SMOOTH_DELAY_MS);
        }
    } else {
        pwm->setPWM(channel, 0, targetHW);
    }
}

void SpiderServo::setAngle(double a) {
    ang = a;
    PWMval = convertAngle(a);
    if (pwm != nullptr) {
        pwm->setPWM(channel, 0, clampPWM(PWMval + trim));
    }
}

void SpiderServo::setTrim(int16_t t) {
    if (t < TRIM_MIN) t = TRIM_MIN;
    if (t > TRIM_MAX) t = TRIM_MAX;
    trim = t;
}

int16_t SpiderServo::getTrim() const {
    return trim;
}

double SpiderServo::convertPWM(int p) {
    int offset = p - PWM_CENTER;
    double percentage = offset / 205.0;
    return percentage * 90.0;
}

int SpiderServo::convertAngle(double a) {
    double percentage = a / 90.0;
    int offset = static_cast<int>(percentage * 205);
    return offset + PWM_CENTER;
}
