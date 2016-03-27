#pragma once
#include "./Command.hpp"
namespace oa {
namespace game {
class CommandAcceptor {
 public:
  virtual ~CommandAcceptor(){};
  virtual void addCommand(Command *) = 0;
  virtual void processCommands() = 0;
};
}
}
