#version 330 core

layout(location = 0) in vec3 aPos;

uniform float size;

uniform vec3 coords;

void main() {
    gl_Position = vec4(size * (aPos.x + coords.x), size * (aPos.y + coords.y), size * (aPos.z + coords.z), 1.0);
}