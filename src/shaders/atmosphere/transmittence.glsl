#version 330 core

#define TRANSMITTANCE_NON_LINEAR 
layout(location=0) out vec4 transmittanceSampler;

uniform vec2 textureDimensions;
//uniform vec3 betaMSca;
//uniform vec3 betaR;
//uniform float HR;
//uniform float HM;

//uniform float Rg;
//uniform float Rt;
//uniform float RL;

const float Rg = 6378.1;
const float Rt = Rg+60;
const float RL = Rt+1;
const float HR = 8.0;
const float HM = 1.2;
const vec3 betaMSca = vec3(4e-3, 4e-3, 4e-3);
const vec3 betaR    = vec3(5.8e-3,1.35e-2, 3.31e-2);


const int TRANSMITTANCE_INTEGRAL_SAMPLES = 500;

// nearest intersection of ray r,mu with ground or top atmosphere boundary
// mu=cos(ray zenith angle at ray origin)
vec3 betaMEx = betaMSca / 0.9;
float limit(float r, float mu) {
    float dout = -r * mu + sqrt(r * r * (mu * mu - 1.0) + RL * RL);
    float delta2 = r * r * (mu * mu - 1.0) + Rg * Rg;
    if (delta2 >= 0.0) {
        float din = -r * mu - sqrt(delta2);
        if (din >= 0.0) {
            dout = min(dout, din);
        }
    }
    return dout;
}


void getTransmittanceRMu(out float r, out float muS) {
    r = gl_FragCoord.y / textureDimensions.y;
    muS = gl_FragCoord.x / textureDimensions.x;
#ifdef TRANSMITTANCE_NON_LINEAR
    r = Rg + (r * r) * (Rt - Rg);
    muS = -0.15 + tan(1.5 * muS) / tan(1.5) * (1.0 + 0.15);
#else
    r = Rg + r * (Rt - Rg);
    muS = -0.15 + muS * (1.0 + 0.15);
#endif
}




float opticalDepth(float H, float r, float mu) {
    float result = 0.0;
    float dx = limit(r, mu) / float(TRANSMITTANCE_INTEGRAL_SAMPLES);
    float xi = 0.0;
    float yi = exp(-(r - Rg) / H);
    for (int i = 1; i <= TRANSMITTANCE_INTEGRAL_SAMPLES; ++i) {
        float xj = float(i) * dx;
        float yj = exp(-(sqrt(r * r + xj * xj + 2.0 * xj * r * mu) - Rg) / H);
        result += (yi + yj) / 2.0 * dx;
        xi = xj;
        yi = yj;
    }
    return mu < -sqrt(1.0 - (Rg / r) * (Rg / r)) ? 1e9 : result;
}

void main(){
    float r, muS;
    getTransmittanceRMu(r, muS);
    vec3 depth = betaR * opticalDepth(HR, r, muS) + betaMEx * opticalDepth(HM, r, muS);
    transmittanceSampler = vec4(exp(-depth), 0.0); // Eq (5)
}
