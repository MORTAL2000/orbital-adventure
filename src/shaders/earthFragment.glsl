#version 330 core


uniform sampler2D west;
uniform sampler2D east;
uniform sampler2D hmWest;
uniform sampler2D hmEast;

uniform sampler2D finest;
uniform sampler2D finestNE;
uniform sampler2D finestNW;
uniform sampler2D finestN;
uniform sampler2D finestS;
uniform sampler2D finestSE;
uniform sampler2D finestSW;
uniform sampler2D finestW;
uniform sampler2D finestE;

//uniform sampler2D transmittanceSampler;
//uniform sampler2D deltaESampler;
//uniform sampler2D irradianceSampler;
//uniform sampler3D inscatterSampler;
//uniform sampler3D deltaSMSampler;
//uniform sampler3D deltaSRSampler;
//uniform sampler3D inscatter1Copy;
uniform float time;


uniform vec2  currentCameraUV;
uniform ivec2 lodGridDimention;
uniform ivec2 currentGridCenter;
uniform vec3 sunDirection;


in vec2 uv;
in vec2 attrUV;
in vec3 norm;
in vec4 pos;
in vec3 fragNormal;
out vec4 color;




float d = 0.002;

float PI = 3.1415926535897932384626433832795;


float periodize(float v, float p){
    return mod(v,p)/p;
}

float periodize(float v, float p, float s, float w){
    return s + periodize(v,p) * w;
}

bool hasUpperTexel(vec2 uv, ivec2 gridElement){
    ivec2 c = ivec2(uv.x * float(lodGridDimention.x), uv.y * float(lodGridDimention.y));
    return c == gridElement;
}

vec2 calculateUV(){
    vec2 nuv;

    float ang = mod(asin(pos.z) / PI + 1.5, 1.0);
    float lonAngle = atan(pos.y, pos.x);
    float lon = mod(atan(pos.y, pos.x) / (2*PI) + 1.0, 1.0);

    return vec2( lon, 1.0 - ang);

}

vec4 getUpperTexel(vec2 uv, sampler2D tex, out vec2 nuv){
    
    vec2 suv = vec2(mod(uv.x,1.0 / lodGridDimention.x)* lodGridDimention.x,
            mod(  uv.y, lodGridDimention.y)*lodGridDimention.y);
    nuv = suv;
    vec4 t = texture(tex, suv);
    return t;
}
vec4 getUpperTexel(vec2 uv, sampler2D tex){
    
    vec2 suv = vec2(mod(uv.x,1.0 / lodGridDimention.x)* lodGridDimention.x,
            mod(  uv.y, lodGridDimention.y)*lodGridDimention.y);
    vec4 t = texture(tex, suv);
    return t;
}

void getLowerTexel(vec2 nuv, out vec4 texel){
    vec2 sampleUV = nuv;

    int ix = int(nuv.x / 0.5);
    sampleUV.x = mod(nuv.x, 0.5)*2.0;
    sampleUV.y = (nuv.y);

    if     (ix == 0 ) texel = texture(west,sampleUV);
    else if(ix == 1 ) texel = texture(east,sampleUV);
    else texel = vec4(1.0, 0.0, 1.0, 1.0);
}

vec4 lookupLOD(in vec2 uv,  vec4 texel ){
    for(int w =  -1; w <= 1; ++w){
        for(int h = -1; h <= 1; ++h){

            ivec2 tile = ivec2(currentGridCenter.x + w, currentGridCenter.y + h);
            if(hasUpperTexel(uv, tile)){
                if(w == -1 && h == -1) return getUpperTexel(uv, finestNE);
                if(w == -1 && h == 0) return getUpperTexel(uv, finestN);
                if(w == -1 && h == 1) return getUpperTexel(uv, finestNW);
                if(w == 0  && h == -1) return getUpperTexel(uv, finestE);
                //if(w == 0  && h == 0 ) return getUpperTexel(uv, finest);
                if(w == 0  && h == 0 ){
                    vec2 _uv;
                    vec4 ut = getUpperTexel(uv, finest, _uv);
                    //vec4 t =abs(texture(inscatterSampler, vec3(_uv,periodize(time, 2.0, 0.0, 1.0))));
 

                    return vec4(ut.rgba);                    
                    //return getUpperTexel(uv, deltaESampler)*10.0;
                }
                if(w == 0  && h == 1) return getUpperTexel(uv, finestW);
                if(w == 1  && h == -1) return getUpperTexel(uv, finestSE);
                if(w == 1  && h == 0) return  getUpperTexel(uv, finestS);
                if(w == 1  && h == 1) return getUpperTexel(uv, finestSW);
            }
        }
    } 
    return texel;
}

void main(){

    vec2 uv = calculateUV();
    vec4 texel;
    getLowerTexel(uv, texel);

    texel = lookupLOD(uv, texel);
    float red = length(uv - currentCameraUV) < d? 1.0: 0.0;
    texel.r += red;

    float intense = clamp(dot(sunDirection, fragNormal), 1.0, 1.0);

    // texel = vec4(abs(norm),1.0);
    //texel = vec4(1.0);
    color =  vec4( texel.rgb*intense  ,  1.0);

}

