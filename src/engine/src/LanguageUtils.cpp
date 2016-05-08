#include <cmath>
#include "LanguageUtils.hpp"
namespace oa {
namespace utils {
long double operator"" _pi(long double r) { return r * M_PI; }
long double operator"" _pi(unsigned long long int r) {
  return double(r) * M_PI;
}

std::ostream &operator<<(std::ostream &s, const glm::mat3 &m) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      s << m[i][j] << "  ";
    }
    s << "\n";
  }
  return s;
}

std::ostream &operator<<(std::ostream &s, const glm::mat4 &m) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      s << m[i][j] << "  ";
    }
    s << "\n";
  }
  return s;
}

std::ostream &operator<<(std::ostream &s, const glm::quat &m) {
  s << m.w << ", " << m.x << ", " << m.y << ", " << m.x;
  return s;
}

std::ostream &operator<<(std::ostream &s, const glm::vec4 &m) {
  s << m.x << ", " << m.y << ", " << m.z << ", " << m.w;
  return s;
}

std::ostream &operator<<(std::ostream &s, const glm::vec3 &m) {
  s << m.x << ", " << m.y << ", " << m.z;
  return s;
}

std::ostream &operator<<(std::ostream &s, const glm::vec2 &m) {
  s << m.x << ", " << m.y;
  return s;
}
}
}
