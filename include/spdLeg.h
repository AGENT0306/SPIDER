#ifndef SPDLEG_H
#define SPDLEG_H

#include "spdServo.h"
#include "spdIK.h"

class SPDLegs {
public:
    SPDLegs();
    SPDLegs(const int channels[3], Adafruit_PWMServoDriver* pwm);
    void setAngles(const JointAngles& angles);
    void setPWMs(const uint16_t pwm[3]);
    void moveLeg(const double angles[3]);
    SpiderServo& getServo(int joint);
private:
    SpiderServo servos[3];
};

#endif //SPDLEG_H
