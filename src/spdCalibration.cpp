#include "../include/spdCalibration.h"
#include <Preferences.h>

static SpiderServo& getServoByIdx(SPDLegs* legs, int idx) {
    int leg = idx % NUM_LEGS;
    int joint = idx / NUM_LEGS;
    return legs[leg].getServo(joint);
}

void SpdCalibration::loadTrims(SPDLegs* legs) {
    Preferences prefs;
    prefs.begin(CAL_NVS_NAMESPACE, true); // read-only
    for (int i = 0; i < NUM_SERVOS; i++) {
        char key[4];
        snprintf(key, sizeof(key), "t%d", i);
        int16_t t = prefs.getShort(key, 0);
        getServoByIdx(legs, i).setTrim(t);
    }
    prefs.end();
    Serial.println("Trims loaded from NVS");
}

void SpdCalibration::saveTrims(SPDLegs* legs) {
    Preferences prefs;
    prefs.begin(CAL_NVS_NAMESPACE, false); // read-write
    for (int i = 0; i < NUM_SERVOS; i++) {
        char key[4];
        snprintf(key, sizeof(key), "t%d", i);
        prefs.putShort(key, getServoByIdx(legs, i).getTrim());
    }
    prefs.end();
    Serial.println("Trims saved to NVS");
}

static void printAllTrims(SPDLegs* legs) {
    Serial.println("--- Servo Trims ---");
    for (int i = 0; i < NUM_SERVOS; i++) {
        SpiderServo& s = getServoByIdx(legs, i);
        Serial.print("Servo ");
        Serial.print(i);
        Serial.print(" (ch ");
        Serial.print(s.getChannel());
        Serial.print("): trim=");
        Serial.println(s.getTrim());
    }
    Serial.println("-------------------");
}

void SpdCalibration::enterCalMode(SPDLegs* legs) {
    Serial.println("=== Calibration Mode ===");
    Serial.println("Commands: 0-11 (select servo), +/- (nudge 1), ++/-- (nudge 5)");
    Serial.println("          c (center), p (print trims), s (save), exit");

    int selected = 0;
    Serial.print("Selected servo: ");
    Serial.println(selected);

    while (true) {
        if (!Serial.available()) {
            delay(50);
            continue;
        }

        String cmd = Serial.readStringUntil('\n');
        cmd.trim();

        if (cmd == "exit") {
            Serial.println("Exiting calibration mode");
            break;
        } else if (cmd == "p") {
            printAllTrims(legs);
        } else if (cmd == "s") {
            saveTrims(legs);
        } else if (cmd == "c") {
            // Center selected servo at PWM_CENTER + trim
            SpiderServo& s = getServoByIdx(legs, selected);
            s.setPWM(PWM_CENTER);
            Serial.print("Centered servo ");
            Serial.println(selected);
        } else if (cmd == "++") {
            SpiderServo& s = getServoByIdx(legs, selected);
            s.setTrim(s.getTrim() + 5);
            s.setPWM(s.getPWM()); // re-apply to see effect
            Serial.print("Trim: ");
            Serial.println(s.getTrim());
        } else if (cmd == "--") {
            SpiderServo& s = getServoByIdx(legs, selected);
            s.setTrim(s.getTrim() - 5);
            s.setPWM(s.getPWM());
            Serial.print("Trim: ");
            Serial.println(s.getTrim());
        } else if (cmd == "+") {
            SpiderServo& s = getServoByIdx(legs, selected);
            s.setTrim(s.getTrim() + 1);
            s.setPWM(s.getPWM());
            Serial.print("Trim: ");
            Serial.println(s.getTrim());
        } else if (cmd == "-") {
            SpiderServo& s = getServoByIdx(legs, selected);
            s.setTrim(s.getTrim() - 1);
            s.setPWM(s.getPWM());
            Serial.print("Trim: ");
            Serial.println(s.getTrim());
        } else {
            // Try to parse as servo number
            int num = cmd.toInt();
            if (num >= 0 && num < NUM_SERVOS && (cmd == "0" || num != 0)) {
                selected = num;
                SpiderServo& s = getServoByIdx(legs, selected);
                s.setPWM(PWM_CENTER); // center it on selection
                Serial.print("Selected servo ");
                Serial.print(selected);
                Serial.print(" (ch ");
                Serial.print(s.getChannel());
                Serial.print("), trim=");
                Serial.println(s.getTrim());
            } else {
                Serial.println("Unknown command");
            }
        }
    }
}
