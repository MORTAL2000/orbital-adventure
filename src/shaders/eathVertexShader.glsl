#version 330 core

layout(location=0)in vec3 position;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 uvAttr;

uniform sampler2D hmWest;
uniform sampler2D hmEast;


uniform mat4 modelViewProjection;
uniform mat4 northPoleToCameraRotation;

vec2 textureResolution = vec2(4096,4096);

out vec2 uv;
out vec2 attrUV;
out vec4 pos;
out vec3 fragNormal;
out vec3 norm;


float PI = 3.1415926;


float weightedLookupRed(sampler2D tex, vec2 nuv){
    vec2 pixelSize = 1. / textureResolution;
    vec2 duv = mod(nuv, pixelSize);
    vec2 uv0 = nuv - duv;
    vec2 uv1 = uv + pixelSize;
    float s1 = (nuv.x - uv0.x) * pixelSize.x;
    float s0 = 1.0 - s1;
    float t1 = (nuv.y - uv0.y) * pixelSize.y;
    float t0 = 1.0 - t1;

    float tsumm1 = t0 * texture(tex, uv0).r 
        + t1 * texture(tex,vec2(uv0.x, uv1.y)).r; 

    float tsumm2 = t0 * texture(tex, vec2(uv1.x,uv0.y)).r 
        + t1 * texture(tex,uv1).r; 

    float summ = s0*(tsumm1) + s1*(tsumm2);
    return summ;
}

void getHeight(vec2 nuv, out float height){
    vec2 sampleUV = nuv;

    int ix = int(nuv.x / 0.5);
    sampleUV.x = mod(nuv.x, 0.5)*2.0;
    sampleUV.y = (1.0-nuv.y);


    if (ix == 0 ) height = weightedLookupRed(hmWest,sampleUV);
    else if(ix == 1 ) height = weightedLookupRed(hmEast,sampleUV);
}

void main(void){

    attrUV = uvAttr;

    pos = northPoleToCameraRotation *   vec4(position, 1.0);
    float ang = mod(asin(pos.z) / PI + 1.5, 1.0);
    float lonAngle = atan(pos.y, pos.x);
    float lon = mod(atan(pos.y, pos.x) / (2*PI) + 1.0, 1.0);
    uv = vec2( lon, ang);
    norm = normal;
    fragNormal = (northPoleToCameraRotation * vec4(normal,0.0)).xyz;

    float height;
    getHeight(uv, height);
    vec4 pp = pos + vec4(fragNormal* length(height)*0.010, .0);
     


    gl_Position = modelViewProjection * pp;

    
}

