#version 400 core

uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 position;

out vec3 pos_object;

const float scale = 12.;

void main() {
     pos_object = vec3(-position.x, position.yz);;
     gl_Position = projection * view * vec4(position * scale, 1);
}
