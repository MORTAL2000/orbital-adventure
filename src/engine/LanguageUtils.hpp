#pragma once
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
namespace oa {
namespace utils {
long double operator"" _pi(long double r);
long double operator"" _pi(unsigned long long int r);

std::ostream &operator<<(std::ostream &s, const glm::mat4 &m);
std::ostream &operator<<(std::ostream &s, const glm::mat3 &m);
std::ostream &operator<<(std::ostream &s, const glm::vec3 &m);
std::ostream &operator<<(std::ostream &s, const glm::vec4 &m);
std::ostream &operator<<(std::ostream &s, const glm::vec2 &m);
std::ostream &operator<<(std::ostream &s, const glm::quat &m);
}
}
