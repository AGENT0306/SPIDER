#ifndef SPIDER_SPDCALIBRATION_H
#define SPIDER_SPDCALIBRATION_H

#include "spdLeg.h"
#include "spdConfig.h"

namespace SpdCalibration {
    // Load saved trims from NVS and apply to all servos
    void loadTrims(SPDLegs* legs);

    // Save current trims to NVS
    void saveTrims(SPDLegs* legs);

    // Interactive serial calibration mode
    void enterCalMode(SPDLegs* legs);
}

#endif //SPIDER_SPDCALIBRATION_H
