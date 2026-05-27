#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;

void main() {
    gl_Position = vec4(inPos, 1.0f);
}
