#include "../include/spdLeg.h"

SPDLegs::SPDLegs() {
}

SPDLegs::SPDLegs(const int channels[3], Adafruit_PWMServoDriver* pwm) {
    for (int i = 0; i < 3; i++) {
        servos[i] = SpiderServo(channels[i], pwm);
    }
}

void SPDLegs::setAngles(const JointAngles& angles) {
    servos[0].setAngle(angles.coxa);
    servos[1].setAngle(angles.femur);
    servos[2].setAngle(angles.tibia);
}

void SPDLegs::setPWMs(const uint16_t pwm[3]) {
    for (int i = 0; i < 3; i++) {
        servos[i].setPWM(pwm[i]);
    }
}

void SPDLegs::moveLeg(const double angles[3]) {
    for (int i = 0; i < 3; i++) {
        servos[i].setAngle(angles[i]);
    }
}

SpiderServo& SPDLegs::getServo(int joint) {
    return servos[joint];
}
