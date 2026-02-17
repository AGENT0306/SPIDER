#include "../include/dev.h"
#include <Arduino.h>

void devMode(Adafruit_PWMServoDriver& pwm) {
    Serial.println("You have entered Dev Mode");
    Serial.println("Use this mode to test various servos and their limits");
    Serial.println("Enter servo channel number, or 'exit' to quit");
    delay(1000);
    while (true) {
        if (Serial.available()) {
            String test = Serial.readStringUntil('\n');
            test.trim();
            if (test == "exit") {
                break;
            } else {
                testServo(test.toInt(), pwm);
            }
        }
        delay(50);
    }
}

void testServo(int sNum, Adafruit_PWMServoDriver& p) {
    Serial.print("Testing servo ");
    Serial.println(sNum);
    for (int i = 307; i > 150; i--) {
        p.setPWM(sNum, 0, i);
        delay(10);
    }
    delay(500);
    for (int z = 150; z < 500; z++) {
        p.setPWM(sNum, 0, z);
        delay(10);
    }
    // Return to center
    for (int i = 500; i > 307; i--) {
        p.setPWM(sNum, 0, i);
        delay(10);
    }
}
