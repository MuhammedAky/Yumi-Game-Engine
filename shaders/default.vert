#version 330 core

layout(location = 0) in vec3 aPos;

uniform float size;

uniform vec3 coords;

// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * model * vec4(size * (aPos.x + coords.x), size * (aPos.y + coords.y), size * (aPos.z + coords.z), 1.0);
}