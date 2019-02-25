#version 330
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec4 color;
uniform vec2 transition;
uniform vec2 resolution;

out vec2 UV;
out vec4 fontColor;
void main(){
    vec2 pos = (position +transition)*2/resolution - 1.0;
    fontColor = color;
    UV = uv;
    //gl_Position = vec4(pos, 0.0, 1.0);
    gl_Position = vec4(pos, 0.0, 1.0);

}

