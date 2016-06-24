#pragma once
#include <array>
#include "engine/Curve.hpp"

namespace oa {
namespace rocket {
class RocketStage {
  typedef oa::geometry::Curve Curve;
  enum StageForm { CYLINDER, CONE, SPHERE };
  class Mount {};
  class Device {
    Mount mount;
  };

  class Shape {
    StageForm form;
    std::array<Curve, 4> sideCurves;
    std::array<Curve, 2> capCurves;  // cap cureves must have
                                     // same segement number;
  };

  struct Pipable {};
  class Source : public Pipable {};
  class Sink : public Pipable {};

  class Tank {
    Shape shape;
    float width;  // ширина стенки
    glm::vec3 drainPoint;
  };

  class Engine {
    Sink fuel;
    Sink oxidizer;
    Sink vector;
  };

  class EnginePlacement {
    Engine engine;
    Source source;
  };

  class Pipe : public Pipable {
    Curve curve;
    Curve diameter;
    float width;  // ширина стенки
    Pipable source, sink;
  };

  // Stageform is defined by formfactor and several interpolated bezier curves
  Shape stageForm;
  std::vector<Tank> fuelTanks;  // fuel tanks are shapes within rocket;
  std::vector<Mount> mounts;
  std::vector<Device> devices;
  std::vector<EnginePlacement> engines;
  std::vector<Pipe> pipes;  // and wires;
};
}
}
