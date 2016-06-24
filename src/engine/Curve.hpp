#include <glm/vec3.hpp>
#include <vector>
namespace oa {
namespace geometry {
class Curve {
  class _CurveSegment {
    glm::vec3 p0, p1, p2, p3;
  };
  std::vector<_CurveSegment> segments;
};
}
}
