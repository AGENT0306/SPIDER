#ifndef SPIDER_SPDMOVES_H
#define SPIDER_SPDMOVES_H

#include "spdLeg.h"
#include "spdIK.h"
#include "spdConfig.h"

struct Keyframe {
    FootPosition feet[4];  // XYZ target for each leg
    uint16_t duration_ms;  // hold time after reaching this pose
};

struct Movement {
    const Keyframe* frames;
    uint8_t numFrames;
    bool loop;
};

enum MoveID : uint8_t {
    MOVE_REST,
    MOVE_STAND,
    MOVE_SIT,
    MOVE_WALK_FWD,
    MOVE_WALK_BACK,
    MOVE_TURN_LEFT,
    MOVE_TURN_RIGHT,
    MOVE_WAVE,
    MOVE_COUNT
};

class SpiderMoves {
public:
    SpiderMoves(SPDLegs* legs);
    void execute(MoveID id);
    void stop();
private:
    SPDLegs* legs;
    volatile bool stopFlag;
    void applyKeyframe(const Keyframe& kf);
};

#endif //SPIDER_SPDMOVES_H
