#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 projectionInverse;
uniform mat4 viewInverse;
out vec3 rayVS;
out vec3 coordsVS;
void main() {
  coordsVS = position;
  rayVS = (viewInverse * vec4((projectionInverse * vec4(position, 0.0)).xyz, 0.0)).xyz;
  gl_Position = vec4(position, 1.0);
}
