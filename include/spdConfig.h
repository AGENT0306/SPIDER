#ifndef SPIDER_SPDCONFIG_H
#define SPIDER_SPDCONFIG_H

#include <cmath>

// --- Leg segment lengths (mm) - MEASURE AND UPDATE THESE ---
constexpr float COXA_LENGTH  = 30.0f;
constexpr float FEMUR_LENGTH = 50.0f;
constexpr float TIBIA_LENGTH = 70.0f;

// --- Body dimensions (mm) ---
constexpr float BODY_WIDTH  = 80.0f;
constexpr float BODY_LENGTH = 100.0f;

// --- Leg mount positions relative to body center (mm) ---
// Order: FL=0, FR=1, RL=2, RR=3
constexpr float LEG_MOUNT_X[4] = {
     BODY_LENGTH / 2,   // FL
     BODY_LENGTH / 2,   // FR
    -BODY_LENGTH / 2,   // RL
    -BODY_LENGTH / 2    // RR
};
constexpr float LEG_MOUNT_Y[4] = {
     BODY_WIDTH / 2,    // FL
    -BODY_WIDTH / 2,    // FR
     BODY_WIDTH / 2,    // RL
    -BODY_WIDTH / 2     // RR
};

// Yaw angle of each leg mount (radians)
constexpr float LEG_MOUNT_YAW[4] = {
     M_PI / 4,          // FL: 45 deg
    -M_PI / 4,          // FR: -45 deg
     3 * M_PI / 4,      // RL: 135 deg
    -3 * M_PI / 4       // RR: -135 deg
};

// --- Servo channel map: {coxa, femur, tibia} per leg ---
constexpr int SERVO_CHANNELS[4][3] = {
    {0, 4, 8},
    {1, 5, 9},
    {2, 6, 10},
    {3, 7, 12}
};

constexpr int NUM_LEGS    = 4;
constexpr int NUM_SERVOS  = 12;

// --- PWM constants ---
constexpr int PWM_MIN     = 102;
constexpr int PWM_MAX     = 512;
constexpr int PWM_CENTER  = 307;
constexpr int PWM_FREQ    = 50;
constexpr long OSC_FREQ   = 26000000L;

// --- Gait defaults ---
constexpr float STAND_HEIGHT   = -60.0f;  // z position when standing (negative = below body)
constexpr float STEP_HEIGHT    = 25.0f;   // how high foot lifts during swing
constexpr float STRIDE_LENGTH  = 40.0f;   // forward distance per step
constexpr int   STEP_DURATION  = 500;     // ms per gait cycle
constexpr float DEFAULT_SPEED  = 0.5f;

// --- Servo movement ---
constexpr int SMOOTH_DELAY_MS = 10;       // delay per PWM step for smooth movement

// --- Calibration ---
constexpr const char* CAL_NVS_NAMESPACE = "servo_cal";
constexpr int16_t TRIM_MIN = -50;
constexpr int16_t TRIM_MAX =  50;

// Flat servo index (0-11) to PCA9685 channel
inline int servoIdxToChannel(int idx) {
    int leg = idx % NUM_LEGS;
    int joint = idx / NUM_LEGS;
    return SERVO_CHANNELS[leg][joint];
}

#endif //SPIDER_SPDCONFIG_H
