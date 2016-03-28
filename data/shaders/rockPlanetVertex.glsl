#version 410 core

layout(location=0)in vec3 position;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 uvAttr;


uniform mat4 modelViewMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 uv;


void main(void){
    uv = uvAttr;
    gl_Position = projection *  view * model * vec4(position, 1.0);
}
