#version 410 core

layout(location=0)in vec3 position;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 uvAttr;


uniform mat4 modelViewMatrix;

out vec2 uv;
out vec3 norm;


void main(void){
    uv = uvAttr;
    norm = normal;
    gl_Position = modelViewMatrix * vec4(position, 1.0);
}
