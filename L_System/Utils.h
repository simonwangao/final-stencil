#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

// alphabet
// follow shorturl.at/swMPX at Table 3
const string F = "F";          // Move forward a step of length d
const string f = "f";          // Move forward a step of length d without drawing a line
const string plus = "+";       // Turn left by angle δ around the Y axis
const string minus = "-";      // Turn right by angle δ around the Y axis
const string down = "&";       // Pitch down by angle δ around the X axis
const string up = "^";         // Pitch up by angle δ around the X axis
const string left = "\\";      // Roll left by angle δ around the Z axis
const string right = "/";      // Roll right by angle δ around the Z axis
const string lbracket = "[";   // Push the current state of the turtle to stack
const string rbracket = "]";   // Pop the current state of the turtle from stack

// parameters
const int l_t = 4;          // Branch levels of the tree
const float l_max = 10.;     // The max length allowed of a branch
const float l_min = 0.;     // The min length allowed of a branch
const float alpha_max = 60.; // The max branching angle allowed of a branch
const float alpha_min = 15.; // The min branching angle allowed of a branch
const float w = 4.;         // The width of the initial branch
const float d = 0.707;      // The decrease of the width

struct BranchFeats {
    float l; // length of branch
    float alphaX; // branching angle in X
    float alphaY; // branching angle in Y
    float alphaZ; // branching angle in Z

    BranchFeats(): l(0), alphaX(0), alphaY(0), alphaZ(0) {};
    BranchFeats(float len, float angleX, float angleY, float angleZ): l(len), alphaX(angleX), alphaY(angleY), alphaZ(angleZ) {};
    ~BranchFeats();
};

// map of character to branch characteristics
unordered_map<char, BranchFeats> charToBranch;

// production rules
unordered_map<char, vector<char>> successors;

static void addBranchChar(char character, BranchFeats characteristics);
static void addProductionRule(char predecessor, vector<char> succs);

static float randomLen();
static float randomAngle();

static unordered_map<char, BranchFeats> createBranchTypes();
static unordered_map<char, vector<char>> createProductionRules();

#endif
