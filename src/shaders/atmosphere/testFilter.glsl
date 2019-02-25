#version 330 core

layout(location =0) out vec4 transition;
uniform sampler2D mainRender;
uniform ivec2 viewportResolution;

void main(){
    vec2 uv = gl_FragCoord.xy/ viewportResolution;
    vec4 texel = texture(mainRender, uv);

    transition = texel +  vec4(0.1,0.0 , 0.0, 0.0);
}

