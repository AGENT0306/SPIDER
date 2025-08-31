//
// Created by reitr on 8/18/2025.
//

#ifndef SPIDER_SPDMOVES_H
#define SPIDER_SPDMOVES_H

#include <string>
#include <map>
#include <vector>
#include <spdServo.h>

class SpiderMoves {
public:
    SpiderMoves();
    void doMove(std::string mName);
private:
    std::map<std::string, std::vector<int>> moveSet;
};


#endif //SPIDER_SPDMOVES_H