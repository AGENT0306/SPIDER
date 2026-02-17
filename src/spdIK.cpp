#include "../include/spdIK.h"
#include <cmath>

static float clampAngle(float deg) {
    if (deg < -90.0f) return -90.0f;
    if (deg >  90.0f) return  90.0f;
    return deg;
}

bool legIK(const FootPosition& foot, JointAngles& out) {
    // Step 1: coxa angle — horizontal rotation
    out.coxa = atan2f(foot.y, foot.x) * (180.0f / M_PI);

    // Step 2: project into leg plane
    float groundDist = sqrtf(foot.x * foot.x + foot.y * foot.y);
    float reach = groundDist - COXA_LENGTH;
    float height = foot.z;

    // Step 3: distance from femur pivot to foot
    float dist2 = reach * reach + height * height;
    float dist = sqrtf(dist2);

    float femur2 = FEMUR_LENGTH * FEMUR_LENGTH;
    float tibia2 = TIBIA_LENGTH * TIBIA_LENGTH;

    // Check reachability
    float maxReach = FEMUR_LENGTH + TIBIA_LENGTH;
    float minReach = fabsf(FEMUR_LENGTH - TIBIA_LENGTH);
    if (dist > maxReach || dist < minReach) {
        return false;
    }

    // Step 4: law of cosines for tibia angle
    float cosKnee = (femur2 + tibia2 - dist2) / (2.0f * FEMUR_LENGTH * TIBIA_LENGTH);
    cosKnee = fmaxf(-1.0f, fminf(1.0f, cosKnee));
    // tibia angle: 0 = fully extended, positive = bent
    out.tibia = acosf(cosKnee) * (180.0f / M_PI) - 180.0f;

    // Step 5: femur angle
    float cosAlpha = (femur2 + dist2 - tibia2) / (2.0f * FEMUR_LENGTH * dist);
    cosAlpha = fmaxf(-1.0f, fminf(1.0f, cosAlpha));
    float alpha = acosf(cosAlpha);
    float beta = atan2f(height, reach);
    out.femur = (beta + alpha) * (180.0f / M_PI);

    // Step 6: clamp to servo range
    out.coxa  = clampAngle(out.coxa);
    out.femur = clampAngle(out.femur);
    out.tibia = clampAngle(out.tibia);

    return true;
}
