#version 330 core 

layout(location =0) out vec4 irradianceSampler;


uniform float k; // k=0 for line 4, k=1 for line 10
uniform sampler2D deltaESampler;
uniform vec2 textureDimensions;

void main() {
    vec2 uv = gl_FragCoord.xy / textureDimensions;
    irradianceSampler = k * texture2D(deltaESampler, uv); // k=0 for line 4, k=1 for line 10
}

