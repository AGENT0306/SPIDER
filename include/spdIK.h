#ifndef SPIDER_SPDIK_H
#define SPIDER_SPDIK_H

#include "spdConfig.h"

struct FootPosition {
    float x, y, z;
};

struct JointAngles {
    float coxa, femur, tibia; // degrees
};

// 3-DOF leg-frame inverse kinematics.
// Foot position is relative to coxa joint origin.
// X = forward (along coxa axis), Y = lateral, Z = vertical (negative = down).
// Returns false if position is unreachable.
bool legIK(const FootPosition& foot, JointAngles& out);

#endif //SPIDER_SPDIK_H
