#version 410 core

in vec2 uv;
in vec3 norm;
out vec4 color;


void main(){
    float a = length(uv);
    vec3 n = norm;
    // n.x += §0.5;
    color = vec4( n,  1.0);
}
