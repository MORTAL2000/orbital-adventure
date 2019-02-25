#version 330
layout(location=0)in vec3 position;

uniform vec3 CameraPosition;
uniform mat4x4 ViewProjectionMatrix;


out vec3 TexCoord;

void main()
{
    //TexCoord = vec3(position.x, -position.yz);
    TexCoord = vec3(position.x, position.z, position.y)/1000.0;
    gl_Position = ViewProjectionMatrix * vec4(position + CameraPosition, 1.0);
}
