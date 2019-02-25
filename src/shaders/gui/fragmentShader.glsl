#version 330

layout(location = 0) out vec4 gui;

uniform sampler2D font;
uniform vec2 resolution;
in vec2 UV;
in vec4 fontColor;

void main(){
    vec2 uv =  gl_FragCoord.xy / resolution;

    //float vmask = texture(font, UV).a;
    vec4 tex = texture(font, UV);
    gui = fontColor * tex.a;
    //if(tex.a > 0.9)
    gui.a =  tex.a ;

    //gui.ba =uv;
    //gui.r = 1.0;
    //gui.g = 1.0;
    //gui.b = 1.0;
    //gui.a = 1.0;
}
