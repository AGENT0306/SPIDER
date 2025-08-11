#include <spdLeg.h>

SPDLegs::SPDLegs(Adafruit_PWMServoDriver* p){
    int numL = 0;
    legsIdx = new std::map<int,int>({0,307});
    std::string n = "Uninitialized Set";
    numLegs = &numL;
    setName = &n;
    setPWM = p;
    Serial.println("Uninitialized leg set created!");
}

SPDLegs::SPDLegs(int *nL, std::vector<int> *idx, std::string *n, Adafruit_PWMServoDriver* pwm){
    numLegs = nL;
    legsIdx = new std::map<int,int>;
    setName = n;
    setPWM = pwm;
    for(int i: *idx){
        legsIdx->insert({i, 307});
    }
    pwm->begin();
    pwm->setOscillatorFrequency(26000000);
    pwm->setPWMFreq(50);
    Serial.println("Initialized leg set created!");
}

int SPDLegs::setLegAng(int idx, double ang){


    return 0;
}

//Returns the angle that a specific leg in a set is at from -90 to 90 deg.
double SPDLegs::getLegAng(int idx){
    return convertToAng(legsIdx->at(idx));
}

double SPDLegs::convertToAng(int pwmVal){
    double pwmRatio = pwmVal / 4096.0;
    double angPerc = (pwmRatio - 0.75) / 0.5;
    return angPerc * 90;
}

int SPDLegs::convertToPWM(double ang){
    double angPerc = ang / 90;
    double pwmRatio = (angPerc * 0.5) + 0.75;
    return round(pwmRatio * 4096.0);
}
