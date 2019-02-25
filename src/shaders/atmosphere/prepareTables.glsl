#version 330 core
#define INSCATTER_NON_LINEAR
#define TRANSMITTANCE_NON_LINEAR
uniform sampler2D transmittance;
uniform sampler2D irradiance;
uniform sampler3D deltaSRTexture;
uniform sampler3D deltaSMTexture;
uniform int textureLayer;
uniform int RES_MU_S;
uniform int RES_NU;
uniform int RES_MU;
uniform int RES_R;
uniform float HR;
uniform float HM;
uniform float Rg;
uniform float Rt;
uniform float RL;
uniform vec3 betaR;
uniform vec3 betaMSca;

const int orderFrom = 2;
const int orderTo = 4;
const int TRANSMITTANCE_INTEGRAL_SAMPLES = 500;
const int INSCATTER_INTEGRAL_SAMPLES = 50;
const int IRRADIANCE_INTEGRAL_SAMPLES = 32;
const int INSCATTER_SPHERICAL_INTEGRAL_SAMPLES = 16;
const float dphi = M_PI / float(INSCATTER_SPHERICAL_INTEGRAL_SAMPLES);
const float dtheta = M_PI / float(INSCATTER_SPHERICAL_INTEGRAL_SAMPLES);

vec4 getInitialS(){ 
    vec3 uvw = vec3(gl_FragCoord.xy, float(textureLayer) + 0.5) / vec3(ivec3(RES_MU_S * RES_NU, RES_MU, RES_R));
    vec4 ray = texture3D(deltaSRTexture, uvw);
    vec4 mie = texture3D(deltaSMTexture, uvw);
    return vec4(ray.rgb, mie.r); // store only red component of single Mie scattering (cf. "Angular precision")

}

vec2 getTransmittanceUV(float r, float mu) {
    float uR, uMu;
#ifdef TRANSMITTANCE_NON_LINEAR
	uR = sqrt((r - Rg) / (Rt - Rg));
	uMu = atan((mu + 0.15) / (1.0 + 0.15) * tan(1.5)) / 1.5;
#else
	uR = (r - Rg) / (Rt - Rg);
	uMu = (mu + 0.15) / (1.0 + 0.15);
#endif
    return vec2(uMu, uR);
}

vec3 getTransmittance(float r, float mu, float d) {
    vec3 result;
    float r1 = sqrt(r * r + d * d + 2.0 * r * mu * d);
    float mu1 = (r * mu + d) / r1;
    if (mu > 0.0) {
        result = min(getTransmittance(r, mu) / getTransmittance(r1, mu1), 1.0);
    } else {
        result = min(getTransmittance(r1, -mu1) / getTransmittance(r, -mu), 1.0);
    }
    return result;
}

vec2 getIrradianceUV(float r, float muS) {
    float uR = (r - Rg) / (Rt - Rg);
    float uMuS = (muS + 0.2) / (1.0 + 0.2);
    return vec2(uMuS, uR);
}

vec3 getIrradiance(sampler2D sampler, float r, float muS) {
    vec2 uv = getIrradianceUV(r, muS);
    return texture2D(sampler, uv).rgb;
}

vec3 getTransmittance(float r, float mu) {
	vec2 uv = getTransmittanceUV(r, mu);
    return texture2D(transmittance, uv).rgb;
}

float phaseFunctionM(float mu) {
	return 1.5 * 1.0 / (4.0 * M_PI) * (1.0 - mieG*mieG) * pow(1.0 + (mieG*mieG) - 2.0*mieG*mu, -3.0/2.0) * (1.0 + mu * mu) / (2.0 + mieG*mieG);
}

float phaseFunctionR(float mu) {
    return (3.0 / (16.0 * M_PI)) * (1.0 + mu * mu);
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
void inscatter(float r, float mu, float muS, float nu, bool isFirst, out vec3 raymie) {
    r = clamp(r, Rg, Rt);
    mu = clamp(mu, -1.0, 1.0);
    muS = clamp(muS, -1.0, 1.0);
    float var = sqrt(1.0 - mu * mu) * sqrt(1.0 - muS * muS);
    nu = clamp(nu, muS * mu - var, muS * mu + var);

    float cthetamin = -sqrt(1.0 - (Rg / r) * (Rg / r));

    vec3 v = vec3(sqrt(1.0 - mu * mu), 0.0, mu);
    float sx = v.x == 0.0 ? 0.0 : (nu - muS * mu) / v.x;
    vec3 s = vec3(sx, sqrt(max(0.0, 1.0 - sx * sx - muS * muS)), muS);

    raymie = vec3(0.0);

    // integral over 4.PI around x with two nested loops over w directions (theta,phi) -- Eq (7)
    for (int itheta = 0; itheta < INSCATTER_SPHERICAL_INTEGRAL_SAMPLES; ++itheta) {
        float theta = (float(itheta) + 0.5) * dtheta;
        float ctheta = cos(theta);

        float greflectance = 0.0;
        float dground = 0.0;
        vec3 gtransp = vec3(0.0);
        if (ctheta < cthetamin) { // if ground visible in direction w
            // compute transparency gtransp between x and ground
            greflectance = AVERAGE_GROUND_REFLECTANCE / M_PI;
            dground = -r * ctheta - sqrt(r * r * (ctheta * ctheta - 1.0) + Rg * Rg);
            gtransp = getTransmittance(Rg, -(r * ctheta + dground) / Rg, dground);
        }

        for (int iphi = 0; iphi < 2 * INSCATTER_SPHERICAL_INTEGRAL_SAMPLES; ++iphi) {
            float phi = (float(iphi) + 0.5) * dphi;
            float dw = dtheta * dphi * sin(theta);
            vec3 w = vec3(cos(phi) * sin(theta), sin(phi) * sin(theta), ctheta);

            float nu1 = dot(s, w);
            float nu2 = dot(v, w);
            float pr2 = phaseFunctionR(nu2);
            float pm2 = phaseFunctionM(nu2);

            // compute irradiance received at ground in direction w (if ground visible) =deltaE
            vec3 gnormal = (vec3(0.0, 0.0, r) + dground * w) / Rg;
            vec3 girradiance = getIrradiance(irradiance, Rg, dot(gnormal, s));

            vec3 raymie1; // light arriving at x from direction w

            // first term = light reflected from the ground and attenuated before reaching x, =T.alpha/PI.deltaE
            raymie1 = greflectance * girradiance * gtransp;

            // second term = inscattered light, =deltaS
            if (isFirst){
                // first iteration is special because Rayleigh and Mie were stored separately,
                // without the phase functions factors; they must be reintroduced here
                float pr1 = phaseFunctionR(nu1);
                float pm1 = phaseFunctionM(nu1);
                vec3 ray1 = texture4D(deltaSRTexture, r, w.z, muS, nu1).rgb;
                vec3 mie1 = texture4D(deltaSMTexture, r, w.z, muS, nu1).rgb;
                raymie1 += ray1 * pr1 + mie1 * pm1;
            } else {
                raymie1 += texture4D(deltaSRTexture, r, w.z, muS, nu1).rgb;
            }

            // light coming from direction w and scattered in direction v
            // = light arriving at x from direction w (raymie1) * SUM(scattering coefficient * phaseFunction)
            // see Eq (7)
            raymie += raymie1 * (betaR * exp(-(r - Rg) / HR) * pr2 + betaMSca * exp(-(r - Rg) / HM) * pm2) * dw;
        }
    }

    // output raymie = J[T.alpha/PI.deltaE + deltaS] (line 7 in algorithm 4.1)
}

vec4 computeDeltaJ(bool isFirst){ 
    // inscatterS.glsl in original method
    vec3 raymie;
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
    inscatter(r, mu, muS, nu, isFirst, raymie);
    return raymie;
}

vec4 compputeDeltaE(){ return vec4(0.0);}
vec4 compputeDeltaS(){ return vec4(0.0);}

void main(){
    bool isFirst = false;

    vec4 E = vec4(0.0);
    vec4 S = getInitialS();
    for(int i = orderFrom; i < orderTo; ++i){
        isFirst = i == orderFrom;
        vec4 deltaJ = computeDeltaJ(isFirst);
        vec4 deltaE = computeDeltaE();
        vec4 deltaS = computeDeltaS();
        E += deltaE;
        S += deltaS;
       
    }
}
