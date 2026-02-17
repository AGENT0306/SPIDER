#ifndef SPIDER_DEV_H
#define SPIDER_DEV_H

#include "Adafruit_PWMServoDriver.h"

void devMode(Adafruit_PWMServoDriver& pwm);
void testServo(int sNum, Adafruit_PWMServoDriver& p);

#endif //SPIDER_DEV_H
