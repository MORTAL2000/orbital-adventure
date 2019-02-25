#version 330 core
layout(location=0) out vec4 deltaESampler;
#define TRANSMITTANCE_NON_LINEAR

uniform sampler2D transmittanceSampler;
uniform vec2 textureDimensions;

uniform float HR;
uniform float HM;
uniform float Rg;
uniform float Rt;
uniform float RL;
int SKY_W =  int(textureDimensions.x);
int SKY_H =  int(textureDimensions.y);

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

vec3 transmittance(float r, float mu) {
	vec2 uv = getTransmittanceUV(r, mu);
    return texture2D(transmittanceSampler, uv).rgb;
}

void getIrradianceRMuS(out float r, out float muS) {
    r = Rg + (gl_FragCoord.y - 0.5) / (float(SKY_H) - 1.0) * (Rt - Rg);
    muS = -0.2 + (gl_FragCoord.x - 0.5) / (float(SKY_W) - 1.0) * (1.0 + 0.2);
}

void main(){
    float r, muS;
    getIrradianceRMuS(r, muS);
    deltaESampler = vec4(transmittance(r, muS) * max(muS, 0.0), 0.0);

}
