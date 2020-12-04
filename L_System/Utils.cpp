#include "L_System/Utils.h"
#include <iostream>

void addBranchChar(char character, BranchFeats characteristics) {
    if (charToBranch.count(character) > 0) {
        string str = "overriding previous branch characteristics for character ";
        std::cout << str.append(&character) << std::endl;
    }
    charToBranch[character] = characteristics;
}

void addProductionRule(char predecessor, vector<char> succs) {
    if (successors.count(predecessor) > 0) {
        string str = "overriding previous production rule for character ";
        std::cout << str.append(&predecessor) << std::endl;
    }

    successors[predecessor] = succs;
}

float randomLen() {
    return fmod((float) rand(), (l_max - l_min)) + l_min;
}

float randomAngle() {
    float abs_val = fmod((float) rand(), (alpha_max - alpha_min)) + alpha_min;

    bool pos = rand() % 2;

    if (pos) {
       return abs_val;
    } else {
        return -abs_val;
    }

}


unordered_map<char, BranchFeats> createBranchTypes() {
    float len1 = randomLen();
    float angleX = randomAngle();
    float angleY = randomAngle();
    float angleZ = randomAngle();
    addBranchChar('a', BranchFeats(len1, angleX, angleY, angleZ));

    float len2 = randomLen();
    float angle2X = randomAngle();
    float angle2Y = randomAngle();
    float angle2Z = randomAngle();
    addBranchChar('b', BranchFeats(len2, angle2X, angle2Y, angle2Z));
    return charToBranch;
}

unordered_map<char, vector<char>> createProductionRules() {
    addProductionRule('a', {'a', 'b', 'a'});
    addProductionRule('b', {'b', 'a'});

    return successors;
}
