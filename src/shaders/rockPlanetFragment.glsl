#version 330 core

uniform sampler2D diffuse;
in vec2 uv;
in vec2 attrUV;
in vec3 norm;
in vec4 pos;
out vec4 color;


float d = 0.002;

float PI = 3.1415926535897932384626433832795;
void main(){
    vec2 nuv;

    float ang = mod(asin(pos.z) / PI + 1.5, 1.0);
    float lonAngle = atan(pos.y, pos.x);
    float lon = mod(atan(pos.y, pos.x) / (2*PI) + 1.0, 1.0);

    nuv  = vec2( lon, ang);
    


    vec4 texel = texture( diffuse, nuv);
    //texel.r += red;


     color = vec4( texel.rgb,  1.0);
    
}
