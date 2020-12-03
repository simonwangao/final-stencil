#ifndef UTILS_H
#define UTILS_H

#include <string>

// alphabet
// follow shorturl.at/swMPX at Table 3
const std::string F = "F";          // Move forward a step of length d
const std::string f = "f";          // Move forward a step of length d without drawing a line
const std::string plus = "+";       // Turn left by angle δ around the Y axis
const std::string minus = "-";      // Turn right by angle δ around the Y axis
const std::string down = "&";       // Pitch down by angle δ around the X axis
const std::string up = "^";         // Pitch up by angle δ around the X axis
const std::string left = "\\";      // Roll left by angle δ around the Z axis
const std::string right = "/";      // Roll right by angle δ around the Z axis
const std::string lbracket = "[";   // Push the current state of the turtle to stack
const std::string rbracket = "]";   // Pop the current state of the turtle from stack

// parameters

#endif
