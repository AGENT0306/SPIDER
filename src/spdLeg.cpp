#include <../include/spdLeg.h>


SPDLegs::SPDLegs(Adafruit_PWMServoDriver* p){
    static int numL = 0;
    //legsIdx = new std::map<int,int>({0,307});
    static std::string n = "Uninitialized Set";
    numLegs = numL;
    setName = n;
    PWM = p;
    PWM->begin();
    PWM->setOscillatorFrequency(26000000);
    PWM->setPWMFreq(50);
    Serial.println("Uninitialized leg set created!");
}

SPDLegs::SPDLegs(int nL, std::vector<int> *idx, std::string n, Adafruit_PWMServoDriver* pwm){
    numLegs = nL;
    setName = std::move(n);
    PWM = pwm;
    PWM->begin();
    PWM->setOscillatorFrequency(26000000);
    PWM->setPWMFreq(50);
    for (int i : *idx) {
        legs->emplace_back(i,PWM);
    }
    Serial.println("Initialized leg set created!");
}

void SPDLegs::doMove(std::string move) {

}

void SPDLegs::moveLeg(std::vector<double>* pos) {
    if (pos->size() == legs->size()) {
        for (int i = 0; i < legs->size(); i++) {
            legs->at(i).setAngle(pos->at(i));
        }
    }else {
        Serial.println("Invalid position vector size");
    }
}
