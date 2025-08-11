//
// Created by reitr on 8/10/2025.
//

#ifndef SPDLEG_H
#define SPDLEG_H




#include <string>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <map>
#include <vector>

class SPDLegs {
public:
    SPDLegs(Adafruit_PWMServoDriver* p);
    SPDLegs(int *nL, std::vector<int>* idx, std::string *n, Adafruit_PWMServoDriver* pwm);
    double getLegAng(int idx);
    int setLegAng(int idx, double ang);

private:
    int* numLegs;
    std::map<int,int>* legsIdx;
    std::string* setName;
    Adafruit_PWMServoDriver* setPWM;
    const int minPulse = 102;
    const int maxPulse = 512;
    const int restPulse = 307;
    double convertToAng(int pwmVal);
    int convertToPWM(double ang);
};


#endif //SPDLEG_H
