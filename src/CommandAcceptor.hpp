#pragma once
#include <queue>
#include "./Command.hpp"
namespace oa {
namespace game {
class CommandAcceptor {
  std::queue<Command *> commandQueue;

 public:
  virtual ~CommandAcceptor(){};
  virtual void addCommand(Command *);
  virtual void processCommands();
};
}
}
