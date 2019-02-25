#version 330

uniform samplerCube CubeMap;

in vec3 TexCoord;

out vec4 color;

void main()
{
    //color = vec4(TexCoord, 1.0);
    color = texture(CubeMap, TexCoord);
}
