#include "L_System/Utils.h"
#include <iostream>

static void addBranchChar(char character, BranchFeats characteristics) {
    if (charToBranch.count(character) > 0) {
        std::cout << "overriding previous branch characteristics for character " + character << std::endl;
    }
    charToBranch[character] = characteristics;
}

static void addProductionRule(char predecessor, vector<char> succs) {
    if (successors.count(predecessor) > 0) {
        std::cout << "overriding previous production rule for character " + predecessor << std::endl;
    }

    successors[predecessor] = succs;
}

static float randomLen() {
    return fmod((float) rand(), (l_max - l_min)) + l_min;
}

static float randomAngle() {
    float abs_val = fmod((float) rand(), (alpha_max - alpha_min)) + alpha_min;

    bool pos = rand() % 2;

    if (pos) {
       return abs_val;
    } else {
        return -abs_val;
    }

}


static unordered_map<char, BranchFeats> createBranchTypes() {
    float len1 = randomLen();
    float angleX = randomAngle();
    float angleY = randomAngle();;
    float angleZ = randomAngle();
    addBranchChar('a', BranchFeats(len1, angleX, angleY, angleZ));

    float len2 = randomLen();
    float angle2X = randomAngle();
    float angle2Y = randomAngle();
    float angle2Z = randomAngle();
    addBranchChar('b', BranchFeats(len2, angle2X, angle2Y, angle2Z));
    return charToBranch;
}

static unordered_map<char, vector<char>> createProductionRules() {
    addProductionRule('a', {'a', 'b', 'a'});
    addProductionRule('b', {'b', 'a'});

    return successors;
}
