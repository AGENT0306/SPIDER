//
// Created by reitr on 8/10/2025.
//

#ifndef SPDLEG_H
#define SPDLEG_H

#include "include.h"

class SPDLegs {
public:
    SPDLegs() {
        numLegs = 0;
        PWM = nullptr;
        setName = "";
        legs = nullptr;
    }
    explicit SPDLegs(Adafruit_PWMServoDriver* p);
    SPDLegs(int nL, std::vector<int>* idx, std::string n, Adafruit_PWMServoDriver* pwm);
    void doMove(std::string move);
    void moveLeg(std::vector<double>* pos);

private:
    int numLegs;
    std::vector<SpiderServo>* legs = new std::vector<SpiderServo>;
    std::string setName;
    Adafruit_PWMServoDriver* PWM;
    const int minPulse = 102;
    const int maxPulse = 512;
    const int restPulse = 307;

};


#endif //SPDLEG_H
