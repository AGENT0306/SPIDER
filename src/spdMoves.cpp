#include "../include/spdMoves.h"

// --- Movement keyframe definitions ---

// REST: all joints centered, feet tucked under body
static const Keyframe restFrames[] = {
    {{{COXA_LENGTH, 0, 0}, {COXA_LENGTH, 0, 0}, {COXA_LENGTH, 0, 0}, {COXA_LENGTH, 0, 0}}, 500}
};

// STAND: feet spread, body raised
static const Keyframe standFrames[] = {
    {{{COXA_LENGTH + 20, 0, STAND_HEIGHT}, {COXA_LENGTH + 20, 0, STAND_HEIGHT},
      {COXA_LENGTH + 20, 0, STAND_HEIGHT}, {COXA_LENGTH + 20, 0, STAND_HEIGHT}}, 500}
};

// SIT: low crouch
static const Keyframe sitFrames[] = {
    {{{COXA_LENGTH + 20, 0, -20.0f}, {COXA_LENGTH + 20, 0, -20.0f},
      {COXA_LENGTH + 20, 0, -20.0f}, {COXA_LENGTH + 20, 0, -20.0f}}, 500}
};

// WALK FORWARD: 4-frame wave gait
// Legs: FL=0, FR=1, RL=2, RR=3
// Sequence: lift FL, swing forward, plant; then FR; then RL; then RR
static const float halfStride = STRIDE_LENGTH / 2.0f;
static const float standX = COXA_LENGTH + 20;

static const Keyframe walkFwdFrames[] = {
    // Frame 1: FL lifts and swings forward, others push back
    {{{standX + halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX - halfStride / 3, 0, STAND_HEIGHT},
      {standX - halfStride / 3, 0, STAND_HEIGHT},
      {standX + halfStride / 3, 0, STAND_HEIGHT}}, STEP_DURATION / 4},
    // Frame 2: FL plants, FR lifts and swings forward
    {{{standX + halfStride, 0, STAND_HEIGHT},
      {standX + halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX - halfStride / 3, 0, STAND_HEIGHT},
      {standX - halfStride / 3, 0, STAND_HEIGHT}}, STEP_DURATION / 4},
    // Frame 3: FR plants, RL lifts and swings forward
    {{{standX, 0, STAND_HEIGHT},
      {standX + halfStride, 0, STAND_HEIGHT},
      {standX + halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX - halfStride / 3, 0, STAND_HEIGHT}}, STEP_DURATION / 4},
    // Frame 4: RL plants, RR lifts and swings forward
    {{{standX, 0, STAND_HEIGHT},
      {standX, 0, STAND_HEIGHT},
      {standX + halfStride, 0, STAND_HEIGHT},
      {standX + halfStride, 0, STAND_HEIGHT + STEP_HEIGHT}}, STEP_DURATION / 4},
};

// WALK BACKWARD: reversed stride direction
static const Keyframe walkBackFrames[] = {
    {{{standX - halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX + halfStride / 3, 0, STAND_HEIGHT},
      {standX + halfStride / 3, 0, STAND_HEIGHT},
      {standX - halfStride / 3, 0, STAND_HEIGHT}}, STEP_DURATION / 4},
    {{{standX - halfStride, 0, STAND_HEIGHT},
      {standX - halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX + halfStride / 3, 0, STAND_HEIGHT},
      {standX + halfStride / 3, 0, STAND_HEIGHT}}, STEP_DURATION / 4},
    {{{standX, 0, STAND_HEIGHT},
      {standX - halfStride, 0, STAND_HEIGHT},
      {standX - halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX + halfStride / 3, 0, STAND_HEIGHT}}, STEP_DURATION / 4},
    {{{standX, 0, STAND_HEIGHT},
      {standX, 0, STAND_HEIGHT},
      {standX - halfStride, 0, STAND_HEIGHT},
      {standX - halfStride, 0, STAND_HEIGHT + STEP_HEIGHT}}, STEP_DURATION / 4},
};

// TURN LEFT: left legs step back, right legs step forward
static const Keyframe turnLeftFrames[] = {
    // Lift FL back, FR forward
    {{{standX - halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX + halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX, 0, STAND_HEIGHT},
      {standX, 0, STAND_HEIGHT}}, STEP_DURATION / 2},
    // Plant FL/FR, lift RL back, RR forward
    {{{standX - halfStride, 0, STAND_HEIGHT},
      {standX + halfStride, 0, STAND_HEIGHT},
      {standX - halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX + halfStride, 0, STAND_HEIGHT + STEP_HEIGHT}}, STEP_DURATION / 2},
};

// TURN RIGHT: right legs step back, left legs step forward
static const Keyframe turnRightFrames[] = {
    {{{standX + halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX - halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX, 0, STAND_HEIGHT},
      {standX, 0, STAND_HEIGHT}}, STEP_DURATION / 2},
    {{{standX + halfStride, 0, STAND_HEIGHT},
      {standX - halfStride, 0, STAND_HEIGHT},
      {standX + halfStride, 0, STAND_HEIGHT + STEP_HEIGHT},
      {standX - halfStride, 0, STAND_HEIGHT + STEP_HEIGHT}}, STEP_DURATION / 2},
};

// WAVE: front-left leg lifts and sweeps, others hold stand
static const Keyframe waveFrames[] = {
    // Lift FL
    {{{standX, 0, STAND_HEIGHT + 40},
      {standX + 20, 0, STAND_HEIGHT},
      {standX + 20, 0, STAND_HEIGHT},
      {standX + 20, 0, STAND_HEIGHT}}, 300},
    // Sweep FL left
    {{{standX, 30, STAND_HEIGHT + 40},
      {standX + 20, 0, STAND_HEIGHT},
      {standX + 20, 0, STAND_HEIGHT},
      {standX + 20, 0, STAND_HEIGHT}}, 300},
    // Sweep FL right
    {{{standX, -30, STAND_HEIGHT + 40},
      {standX + 20, 0, STAND_HEIGHT},
      {standX + 20, 0, STAND_HEIGHT},
      {standX + 20, 0, STAND_HEIGHT}}, 300},
    // Sweep FL left again
    {{{standX, 30, STAND_HEIGHT + 40},
      {standX + 20, 0, STAND_HEIGHT},
      {standX + 20, 0, STAND_HEIGHT},
      {standX + 20, 0, STAND_HEIGHT}}, 300},
    // Return to stand
    {{{standX + 20, 0, STAND_HEIGHT},
      {standX + 20, 0, STAND_HEIGHT},
      {standX + 20, 0, STAND_HEIGHT},
      {standX + 20, 0, STAND_HEIGHT}}, 300},
};

// --- Movement table ---
static const Movement movements[MOVE_COUNT] = {
    {restFrames,      1, false},  // MOVE_REST
    {standFrames,     1, false},  // MOVE_STAND
    {sitFrames,       1, false},  // MOVE_SIT
    {walkFwdFrames,   4, true},   // MOVE_WALK_FWD
    {walkBackFrames,  4, true},   // MOVE_WALK_BACK
    {turnLeftFrames,  2, true},   // MOVE_TURN_LEFT
    {turnRightFrames, 2, true},   // MOVE_TURN_RIGHT
    {waveFrames,      5, false},  // MOVE_WAVE
};

// --- Implementation ---

SpiderMoves::SpiderMoves(SPDLegs* l) : legs(l), stopFlag(false) {
}

void SpiderMoves::applyKeyframe(const Keyframe& kf) {
    for (int i = 0; i < NUM_LEGS; i++) {
        JointAngles angles;
        if (legIK(kf.feet[i], angles)) {
            legs[i].setAngles(angles);
        } else {
            Serial.print("IK unreachable for leg ");
            Serial.println(i);
        }
    }
}

void SpiderMoves::execute(MoveID id) {
    if (id >= MOVE_COUNT) return;

    stopFlag = false;
    const Movement& mov = movements[id];

    do {
        for (uint8_t f = 0; f < mov.numFrames; f++) {
            if (stopFlag) return;
            applyKeyframe(mov.frames[f]);
            delay(mov.frames[f].duration_ms);
        }
    } while (mov.loop && !stopFlag);
}

void SpiderMoves::stop() {
    stopFlag = true;
}
