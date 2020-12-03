#ifndef TURTLE_H
#define TURTLE_H

#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <glm.hpp>
#include <unordered_map>

#include "L_System/Utils.h"

using std::string;
using std::unordered_map;
using std::vector;

class Turtle {
public:
    Turtle();
    ~Turtle();

    void setUpRules();
    string createTreePattern(string predecessor);

private:

    string initial;

    // map of character to branch characteristics
    unordered_map<char, BranchFeats> charToBranch;

    // production rules
    unordered_map<char, vector<char>> successors;

};

#endif // TURTLE_H
