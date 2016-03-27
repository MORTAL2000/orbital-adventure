#pragma once
namespace oa {
namespace game {
class Command {
 public:
  virtual void execute() = 0;
  virtual ~Command(){};
};
}
}
