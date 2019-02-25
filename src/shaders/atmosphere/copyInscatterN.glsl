#version 330 core
layout(location=0) out vec4 inscatterSampler;
#define INSCATTER_NON_LINEAR
#define TRANSMITTANCE_NON_LINEAR
uniform sampler3D deltaSRSampler;
uniform int textureLayer;
uniform int RES_MU_S;
uniform int RES_MU;
uniform int RES_NU;
uniform int RES_R;
uniform float Rg;
uniform float Rt;
uniform float RL;
const float M_PI = 3.141592657;
const float mieG = 0.8;

float phaseFunctionR(float mu) {
    return (3.0 / (16.0 * M_PI)) * (1.0 + mu * mu);
}

// Mie phase function
float phaseFunctionM(float mu) {
	return 1.5 * 1.0 / (4.0 * M_PI) * (1.0 - mieG*mieG) * pow(1.0 + (mieG*mieG) - 2.0*mieG*mu, -3.0/2.0) * (1.0 + mu * mu) / (2.0 + mieG*mieG);
}
void getMuMuSNu(float r, vec4 dhdH, out float mu, out float muS, out float nu) {
    float x = gl_FragCoord.x - 0.5;
    float y = gl_FragCoord.y - 0.5;
#ifdef INSCATTER_NON_LINEAR
    if (y < float(RES_MU) / 2.0) {
        float d = 1.0 - y / (float(RES_MU) / 2.0 - 1.0);
        d = min(max(dhdH.z, d * dhdH.w), dhdH.w * 0.999);
        mu = (Rg * Rg - r * r - d * d) / (2.0 * r * d);
        mu = min(mu, -sqrt(1.0 - (Rg / r) * (Rg / r)) - 0.001);
    } else {
        float d = (y - float(RES_MU) / 2.0) / (float(RES_MU) / 2.0 - 1.0);
        d = min(max(dhdH.x, d * dhdH.y), dhdH.y * 0.999);
        mu = (Rt * Rt - r * r - d * d) / (2.0 * r * d);
    }
    muS = mod(x, float(RES_MU_S)) / (float(RES_MU_S) - 1.0);
    // paper formula
    //muS = -(0.6 + log(1.0 - muS * (1.0 -  exp(-3.6)))) / 3.0;
    // better formula
    muS = tan((2.0 * muS - 1.0 + 0.26) * 1.1) / tan(1.26 * 1.1);
    nu = -1.0 + floor(x / float(RES_MU_S)) / (float(RES_NU) - 1.0) * 2.0;
#else
    mu = -1.0 + 2.0 * y / (float(RES_MU) - 1.0);
    muS = mod(x, float(RES_MU_S)) / (float(RES_MU_S) - 1.0);
    muS = -0.2 + muS * 1.2;
    nu = -1.0 + floor(x / float(RES_MU_S)) / (float(RES_NU) - 1.0) * 2.0;
#endif
}

void main() {
    float mu, muS, nu;
    float r = float(textureLayer) / (RES_R - 1.0);
    float dr = textureLayer == 0? 0.01:(textureLayer == (int(RES_R) -1) ? -0.001:0.0 );

    r = r*r;
    r = sqrt(Rg * Rg + r * (Rt*Rt - Rg*Rg)) + dr;

    float dmin, dmax, dminp, dmaxp;

    dmin = Rt - r;
    dmax = sqrt(r*r - Rg*Rg) + sqrt(Rt*Rt - Rg*Rg);
    dminp = r-Rg;
    dmaxp = sqrt(r*r - Rg*Rg);

    vec4 dhdH = vec4(dmin, dmax, dminp, dmaxp);
    getMuMuSNu(r, dhdH, mu, muS, nu);
    vec3 uvw = vec3(gl_FragCoord.xy, float(textureLayer) + 0.5) / vec3(ivec3(RES_MU_S * RES_NU, RES_MU, RES_R));
    inscatterSampler = vec4(texture3D(deltaSRSampler, uvw).rgb / phaseFunctionR(nu), 0.0);
}

