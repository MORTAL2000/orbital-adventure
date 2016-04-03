#version 410 core

uniform sampler2D diffuse;
in vec2 uv;
in vec3 norm;
out vec4 color;


void main(){
    vec4 c = gl_FragCoord;
     vec4 texel = texture( diffuse, uv);
    color = vec4( texel.rgb,  1.0);
    gl_FragDepth = 1-c.w;
    
}
