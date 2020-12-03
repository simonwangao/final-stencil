#ifndef UTILS_H
#define UTILS_H

#include <string>

using std::string;

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
const int l_t = 0;          // Branch levels of the tree
const float l_max = 0.;     // The max length allowed of a branch
const float l_min = 0.;     // The min length allowed of a branch
const float alpha_max = 0.; // The max branching angle allowed of a branch
const float alpha_min = 0.; // The min branching angle allowed of a branch
const float w = 0.;         // The width of the initial branch
const float d = 0.707;      // The decrease of the width
const int l_l = 0;          // Leafing levels of the tree
const int l_n = 0;          // Leaf number per branch

// instead of generating a string, try generating a vector<pair<string, float>>,
// with first of the pair being a constant in alphabet, second being the parameter

#endif
