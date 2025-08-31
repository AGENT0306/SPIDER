//
// Created by reitr on 8/11/2025.
//

#ifndef SPIDER_SERVO_H
#define SPIDER_SERVO_H

#include "Adafruit_PWMServoDriver.h"

class SpiderServo {
public:
    SpiderServo();
    explicit SpiderServo(int idx, Adafruit_PWMServoDriver* p);
    int getPWM() const;
    int getIndex() const;
    double getAngle() const;
    void setPWM(int p);
    void setAngle(double a);
private:
    const int index;
    int PWMval;
    Adafruit_PWMServoDriver* pwm;
    double ang;
    static double convertPWM(int p);
    static int convertAngle(double a);
};


#endif //SPIDER_SERVO_H