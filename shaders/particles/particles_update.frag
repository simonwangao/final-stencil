﻿#version 330 core

uniform float firstPass;
uniform sampler2D prevPos;
uniform sampler2D prevVel;
uniform int numParticles;

// output from quad.vert
in vec2 uv;

// TODO [Task 15] setup the output locations
layout(location = 0) out vec4 pos;
layout(location = 1) out vec4 vel;

const float PI = 3.14159;
const float dt = 0.0167; // 1 sec/60 fps

/*
    A particle has the following properties:
        - pos.xyz = clip space position
        - pos.w = lifetime in seconds (doesn't change)
        - vel.xyz = clip space velocity
        - vel.w = current age in seconds
*/

// A helpful procedural "random" number generator
float hash(float n) { return fract(sin(n)*753.5453123); }

// Helper functions to procedurally generate lifetimes and initial velocities
// based on particle index
float calculateLifetime(int index) {
    const float MAX_LIFETIME = 4.0;
    const float MIN_LIFETIME = 2.0;
    return MIN_LIFETIME + (MAX_LIFETIME - MIN_LIFETIME) * hash(index * 2349.2693);
}

vec3 calculateInitialVelocity(int index) {
    float theta = PI * hash(index * 872.0238);
    const float MIN_VEL = 0.16;
    const float MAX_VEL = 0.4;
    float velMag = MIN_VEL + (MAX_VEL - MIN_VEL) * hash(index * 98723.345);
    return velMag * vec3(cos(theta), sin(theta), cos(theta));
}

// set initial position to be the positions along the sides of the unit cylinder
//vec3 calculateInitialPosition(int index) {
//    float theta = PI * hash(index * 239.0943);

//}

vec4 initPosition(int index) {
    float theta = 2 * PI * hash(index * 345.12848);
    float y = hash(index * 934.2934);
    return vec4(0.5 * sin(theta), y - 0.5, 0.5 * cos(theta), calculateLifetime(index));
}

vec4 initVelocity(vec4 initPos) {
    float x_scale = hash(initPos.x * 495.8383);
    float y_vel = hash(initPos.y * 917.3408);
    float z_scale = hash(initPos.z * 293.1633);
    return vec4(initPos.x * x_scale, y_vel / 2, initPos.z * z_scale, 0.0);
}

vec4 updatePosition(int index) {
    // TODO [Task 16]
    // - sample prevPos and prevVel at uv
    // - xyz: pos + vel * dt
    // - w component is lifetime, so keep it from the previous position
    vec4 text = texture(prevPos, uv);
    vec4 velText = texture(prevVel, uv);
    return vec4(text.xyz + velText.xyz * dt, text.w);
}

vec4 updateVelocity(int index) {
    const float G = 0.01;
    const float C = .05;
    // TODO [Task 16]
    // - sample prevVel at uv
    // - only force is gravity in y direction.  Add G * dt.
    // - w component is age, so add dt
    vec4 posText = texture(prevPos, uv);
    vec4 velText = texture(prevVel, uv);
    // apply a force back towards the center proportional to displacement
    vec3 newVel = vec3(velText.x * 0.9, velText.y + G * dt, velText.z * 0.9);
    return vec4(newVel, velText.w + dt);
}

void main() {
    int index = int(uv.x * numParticles);
    if (firstPass > 0.5) {
        vec4 initPos = initPosition(index);
        pos = initPos;
        vel = initVelocity(initPos);
    } else {
        pos = updatePosition(index);
        vel = updateVelocity(index);

        if (pos.w < vel.w) {
            vec4 initPos = initPosition(index);
            pos = initPos;
            vel = initVelocity(initPos);
        }
    }
}
