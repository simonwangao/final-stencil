﻿#include "L_System/turtle.h"
#include "glm/gtx/transform.hpp"
#include <iostream>

Turtle::Turtle() {
    m_loc = glm::vec4(0.);
    m_direction = glm::vec4(0., 1., 0., 0.);
    m_loc[3] = 1.;
    m_depth = 0;

    setUpRules();
}

Turtle::~Turtle(){
}

void Turtle::setParameters(int s, float ang, float len, float stem, float branch) {
    random = false;
    size = s;
    branchingAngle = ang;
    branchingLen = len;
    stemWidth = stem;
    branchWidth = branch;
}

void Turtle::setUpRules() {

    m_charToBranch = createBranchTypes();
    m_successors = createProductionRules();
    m_initial = createTreePattern();


}

string Turtle::createTreePattern() {

    string newPattern = "";

    for (int i = 0; i < l_t; i++) {
          newPattern.append("a");
    }

    // return changed string
    return newPattern;
}

vector<pair<string, float>> Turtle::interpretChar(char pred, vector<char> succs) {
    vector<pair<string, float>> output;
    BranchFeats vals = m_charToBranch[pred];

    int num_layers = l_t;
    if (!random) {
        num_layers = size;
        if (pred == 'b') {
            m_charToBranch[pred].l = branchingLen;
            m_charToBranch[pred].w = branchWidth;
            m_charToBranch[pred].alphaX = branchingAngle;
            m_charToBranch[pred].alphaY = branchingAngle;
            m_charToBranch[pred].alphaZ = branchingAngle;
        }
    }

    output.push_back({plus, vals.alphaY});
    output.push_back({left, vals.alphaX});
    output.push_back({down, vals.alphaZ});
    output.push_back({W, vals.w});
    output.push_back({F, vals.l});

    if (pred == 'a') {
        m_charToBranch[pred].l *= len0;
        m_charToBranch[pred].w *= d;
    }

    int num_succs = succs.size();
    for (int i = 0; i < num_succs; i++) {
        output.push_back({lbracket, 0});
        vector<pair<string, float>> subResult = interpretChar(succs[i], {});
        output.reserve(subResult.size());
        output.insert(output.end(), subResult.begin(), subResult.end());
        output.push_back({rbracket, 0});
    }

    output.push_back({plus, vals.alphaY});
    output.push_back({left, vals.alphaX});
    output.push_back({down, vals.alphaZ});
    output.push_back({W, vals.w});
    output.push_back({F, vals.l});

    if (pred == 'b') {

        float rotate_val = ((floorf((float) num_layers / 2.0f) + 1.0f) / num_layers) * 360.f;

        glm::mat3 rotation = glm::mat3(glm::rotate(glm::radians(rotate_val), glm::vec3(0, 1, 0)));
        glm::vec3 rotated = rotation * glm::vec3(vals.alphaX, vals.alphaY, vals.alphaZ);

        m_charToBranch[pred].alphaX = rotated.x;
        m_charToBranch[pred].alphaY = rotated.y;
        m_charToBranch[pred].alphaZ = rotated.z;


    }

    for (int i = 0; i < num_succs; i++) {
        output.push_back({lbracket, 0});
        vector<pair<string, float>> subResult = interpretChar(succs[i], {});
        output.reserve(subResult.size());
        output.insert(output.end(), subResult.begin(), subResult.end());
        output.push_back({rbracket, 0});
    }


    return output;
}

vector<pair<string, float>> Turtle::interpretString() {
    int num_chars = m_initial.size();
    vector<pair<string, float>> output;

    for (int i = 0; i < num_chars; i++) {
        char curr = m_initial[i];
        vector<pair<string, float>> charOutput = interpretChar(curr, m_successors[curr]);
        output.reserve(charOutput.size());
        output.insert(output.end(), charOutput.begin(), charOutput.end());
    }

    return output;
}

/**
 * @brief Turtle::parse parse the given "string" (vector of commands and parameters)
 *        generated by the L system
 * @param str
 */
void Turtle::parse(const std::vector<std::pair<std::string, float>>& str) {
    // clear the cache
    m_loc = glm::vec4(0., 0., 0., 1.); // start from the origin in world space
    m_direction = glm::vec4(0., 1., 0., 0.); // along with the Y axis
    m_matrix = glm::mat4(1.); // identity matrix
    m_depth = 0;

    while(!m_stack.empty())
        m_stack.pop();
    m_segments.clear();

    for (auto pair : str) {
        std::string command = pair.first;

        if (command == W) {
            m_width = pair.second;
        }

        if (command == F) {
            // move forward
            // new segment, need to put in the list
            SegmentData data;
            data.startLoc = m_loc;
            data.length = pair.second;
            data.width = m_width;

            // move to the bottom of the skybox
            glm::mat4 mat = glm::translate(glm::vec3(0., -SKYBOX_LENGTH / 2., 0.));
            data.matrix = mat * m_matrix;

            // already finished the rotation and translation,
            // need to do the scaling here
            // note that need to do the translation from center of the bottom circle
            // to the center of the cylinder
            mat = glm::mat4(1.); // identity matrix
            // scaling
            float diameter = data.width;
            mat = glm::scale(glm::vec3(diameter, data.length, diameter)) * mat;
            mat = glm::translate(glm::vec3(0., data.length / 2., 0.)) * mat; // move "to the ground" (y >= 0)
            data.matrix *= mat;

            data.direction = m_direction;
            data.depth = m_depth;
            m_segments.push_back(data);

            // no need to change direction
            // change the location
            m_loc += pair.second * m_direction;
            // update the matrix
            glm::mat4 translateMatrix = glm::translate(glm::vec3(pair.second * m_direction[0],
                                                       pair.second * m_direction[1],
                                                       pair.second * m_direction[2]));
            m_matrix = translateMatrix * m_matrix;
            // update depth
            m_depth += 1;

        } else if (command == f) {
            // move forward
            // no need to draw a segment

            // no need to change direction
            // change the location
            m_loc += pair.second * m_direction;
            // update the matrix
            glm::mat4 translateMatrix = glm::translate(glm::vec3(pair.second * m_direction[0],
                                                       pair.second * m_direction[1],
                                                       pair.second * m_direction[2]));
            m_matrix = translateMatrix * m_matrix;
            // update depth
            m_depth += 1;

        } else if (command == plus) {
            // no need to change location and depth
            // translate back to origin and then translate back
            glm::mat4 back2origin = glm::translate(-m_loc.xyz());

            glm::mat4 rotator = glm::inverse(back2origin) * glm::rotate(pair.second * (float)M_PI / 180.f, glm::vec3(0, 1, 0)) * back2origin;
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;


        } else if (command == minus) {
            // no need to change location and depth
            // translate back to origin and then translate back
            glm::mat4 back2origin = glm::translate(-m_loc.xyz());

            glm::mat4 rotator = glm::inverse(back2origin) * glm::rotate(pair.second * (float)M_PI / 180.f, glm::vec3(0, -1, 0)) * back2origin;
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;

        } else if (command == down) {
            // no need to change location and depth
            // translate back to origin and then translate back
            glm::mat4 back2origin = glm::translate(-m_loc.xyz());

            glm::mat4 rotator = glm::inverse(back2origin) * glm::rotate(glm::radians(pair.second), glm::vec3(1, 0, 0)) * back2origin;
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;

        } else if (command == up) {
            // no need to change location and depth
            // translate back to origin and then translate back
            glm::mat4 back2origin = glm::translate(-m_loc.xyz());

            glm::mat4 rotator = glm::inverse(back2origin) * glm::rotate(glm::radians(pair.second), glm::vec3(-1, 0, 0)) * back2origin;
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;

        } else if (command == left) {
            // no need to change location and depth
            // translate back to origin and then translate back
            glm::mat4 back2origin = glm::translate(-m_loc.xyz());

            glm::mat4 rotator = glm::inverse(back2origin) * glm::rotate(glm::radians(pair.second), glm::vec3(0, 0, 1)) * back2origin;
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;

        } else if (command == right) {
            // no need to change location and depth
            // translate back to origin and then translate back
            glm::mat4 back2origin = glm::translate(-m_loc.xyz());

            glm::mat4 rotator = glm::inverse(back2origin) * glm::rotate(glm::radians(pair.second), glm::vec3(0, 0, -1)) * back2origin;
            m_direction = rotator * m_direction;
            m_matrix = rotator * m_matrix;

        } else if (command == lbracket) {
            // Push the current state of the turtle to stack
            StackData stackData;
            stackData.loc = m_loc;
            stackData.depth = m_depth;
            stackData.matrix = m_matrix;
            stackData.direction = m_direction;
            m_stack.push(stackData);

        } else if (command == rbracket) {
            // Pop the current state of the turtle from stack
            StackData stackData = m_stack.top();
            m_stack.pop();

            m_loc = stackData.loc;
            m_depth = stackData.depth;
            m_matrix = stackData.matrix;
            m_direction = stackData.direction;
        }
    }

    // branch information is in m_segments, which can be used to draw cylinders
    return;
}

std::vector<SegmentData> Turtle::getSegmentData() {
    return m_segments;
}

