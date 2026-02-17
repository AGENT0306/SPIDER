#ifndef SPIDER_SERVO_H
#define SPIDER_SERVO_H

#include "Adafruit_PWMServoDriver.h"
#include "spdConfig.h"

class SpiderServo {
public:
    SpiderServo();
    SpiderServo(int channel, Adafruit_PWMServoDriver* p);
    int getPWM() const;
    int getChannel() const;
    double getAngle() const;
    void setPWM(int p);
    void setAngle(double a);
    void setTrim(int16_t t);
    int16_t getTrim() const;
private:
    int channel;
    int PWMval;
    int16_t trim;
    Adafruit_PWMServoDriver* pwm;
    double ang;
    int clampPWM(int p) const;
    static double convertPWM(int p);
    static int convertAngle(double a);
};

#endif //SPIDER_SERVO_H
