#version 330 core

in vec2 uv;
in vec3 norm;
out vec4 color;


void main(){
    vec4 c = gl_FragCoord;
     vec4 texel = vec4(1.0, 1.0, 0.0, 1.0);
    color = vec4( texel.rgb,  1.0);
    //gl_FragDepth = 1-c.w;
    
}

