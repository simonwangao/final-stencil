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

struct SegmentData {
    glm::vec4 startLoc;     // start location of the segment
    float length;           // length of the segment
    glm::vec4 direction;    // direction of the segment
    glm::mat4 matrix;       // the matrix to transfer the original primitive
    int depth;              // depth of the branch
};

struct StackData {
    glm::vec4 loc;          // location of the turtle
    glm::vec4 direction;    // direction of the segment
    glm::mat4 matrix;       // the transform matrix to this segment
    int depth;              // depth of the branch
};

class Turtle {
public:
    Turtle();
    ~Turtle();

    void setUpRules();
    string createTreePattern(string predecessor);

    // input is a "string" (vector of constants and parameters)
    void parse(const std::vector<std::pair<std::string, float>>& str);

private:
    glm::vec4 m_loc;        // location of the turtle
    glm::vec4 m_direction;  // direction of the turtle, a normalized vector
    glm::mat4 m_matrix;     // the transform matrix to this step
    int m_depth;            // depth of the branch

    string initial;

    // map of character to branch characteristics
    unordered_map<char, BranchFeats> charToBranch;

    // production rules
    unordered_map<char, vector<char>> successors;

    // the stack used for branching e.g. [ ]
    // store location, direction and current matrix of the turtle
    std::stack<StackData> m_stack;

    // the list of the segments that we need to draw corresponding branches
    std::vector<SegmentData> m_segments;

};

#endif // TURTLE_H
