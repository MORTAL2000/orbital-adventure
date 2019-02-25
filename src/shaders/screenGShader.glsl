#version 330 core
// in vec3 rayVS[];
// in vec3 coordsVS[];
//out vec3 ray;
//out vec3 coords;

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;
uniform int textureLayer;



void main() {
    for(int i =0; i < 3; ++i){
        gl_Position = gl_in[i].gl_Position;
        //ray = rayVS[i];
        //coords = gl_in[i].gl_Position.xyz;
        gl_Layer = textureLayer;
        EmitVertex();
    }
    EndPrimitive();
}

