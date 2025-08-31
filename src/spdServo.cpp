//
// Created by reitr on 8/11/2025.
//

#include <../include/spdServo.h>

SpiderServo::SpiderServo(): index(-1), pwm(nullptr){
    PWMval = 307;
    ang = 0.0;
}

SpiderServo::SpiderServo(const int idx, Adafruit_PWMServoDriver* p): index(idx), pwm(p){
    PWMval = 307;
    ang = 0.0;
}

int SpiderServo::getIndex() const {
    return index;
}

int SpiderServo::getPWM() const {
    return PWMval;
}

double SpiderServo::getAngle() const {
    return ang;
}

void SpiderServo::setPWM(int p) {
    PWMval = p;
    pwm->setPWM(index, 0, PWMval);
    ang = convertPWM(PWMval);
}

void SpiderServo::setAngle(double a) {
    ang = a;
    PWMval = convertAngle(a);
    pwm->setPWM(index, 0, PWMval);
}

double SpiderServo::convertPWM(int p) {
    int offset = p - 307;
    double percentage = offset / 205.0;
    return percentage * 90.0; //PWM val as angle
}

int SpiderServo::convertAngle(double a) {
    double percentage = a / 90.0;
    int offset = percentage * 205;
    return offset + 307; //Angle as PWM val
}

