#include "CommandAcceptor.hpp"
namespace oa {
namespace game {

void CommandAcceptor::processCommands() {
  while (commandQueue.size() > 0) {
    auto command = commandQueue.front();
    command->execute();
    commandQueue.pop();
    delete command;
  }
}

void CommandAcceptor::addCommand(Command *c) { commandQueue.push(c); }
}
}
