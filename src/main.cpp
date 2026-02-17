#include "../include/include.h"
#include "../include/spdMoves.h"
#include "../include/spdCalibration.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

SPDLegs legs[NUM_LEGS];
SpiderMoves* moves = nullptr;

void setup() {
    Serial.begin(115200);
    Serial.println("SPIDER Robot Started!");

    pwm.begin();
    pwm.setOscillatorFrequency(OSC_FREQ);
    pwm.setPWMFreq(PWM_FREQ);

    for (int i = 0; i < NUM_LEGS; i++) {
        legs[i] = SPDLegs(SERVO_CHANNELS[i], &pwm);
    }

    SpdCalibration::loadTrims(legs);

    moves = new SpiderMoves(legs);
    moves->execute(MOVE_REST);

    Serial.println("Commands: rest, stand, sit, walk, walkback, left, right, wave, stop, cal, devmode");
    delay(10);
}

void loop() {
    if (Serial.available() > 0) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();

        if (cmd == "rest") {
            Serial.println("Resting");
            moves->execute(MOVE_REST);
        } else if (cmd == "stand") {
            Serial.println("Standing");
            moves->execute(MOVE_STAND);
        } else if (cmd == "sit") {
            Serial.println("Sitting");
            moves->execute(MOVE_SIT);
        } else if (cmd == "walk") {
            Serial.println("Walking forward");
            moves->execute(MOVE_WALK_FWD);
        } else if (cmd == "walkback") {
            Serial.println("Walking backward");
            moves->execute(MOVE_WALK_BACK);
        } else if (cmd == "left") {
            Serial.println("Turning left");
            moves->execute(MOVE_TURN_LEFT);
        } else if (cmd == "right") {
            Serial.println("Turning right");
            moves->execute(MOVE_TURN_RIGHT);
        } else if (cmd == "wave") {
            Serial.println("Waving");
            moves->execute(MOVE_WAVE);
        } else if (cmd == "stop") {
            moves->stop();
            Serial.println("Stopped");
        } else if (cmd == "cal") {
            SpdCalibration::enterCalMode(legs);
        } else if (cmd == "devmode") {
            devMode(pwm);
        } else {
            Serial.print("Unknown command: ");
            Serial.println(cmd);
        }
    }
    delay(100);
}
