#version 400 core

uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 position;

out vec3 pos_object;

const float scale = 20;

void main() {
     pos_object = position;
     gl_Position = projection * view * vec4(position * scale, 1);
}
