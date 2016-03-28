#version 410 core

in vec2 uv;
in vec3 norm;
out vec4 color;


void main(){
    vec4 c = gl_FragCoord;
    color = vec4( uv, 0.0,  1.0);
    gl_FragDepth = 1-c.w;
    
}
