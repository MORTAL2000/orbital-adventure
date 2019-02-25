#version 330 core
layout (location =0) out vec4 inscatterSampler;

uniform sampler3D deltaSRSampler;
uniform sampler3D deltaSMSampler;
uniform int textureLayer;
uniform int RES_MU_S;
uniform int RES_NU;
uniform int RES_MU;
uniform int RES_R;


void main() {
    vec3 uvw = vec3(gl_FragCoord.xy, float(textureLayer) + 0.5) / vec3(ivec3(RES_MU_S * RES_NU, RES_MU, RES_R));
    vec4 ray = texture3D(deltaSRSampler, uvw);
    vec4 mie = texture3D(deltaSMSampler, uvw);
    inscatterSampler = vec4(ray.rgb, mie.r); // store only red component of single Mie scattering (cf. "Angular precision")
}

