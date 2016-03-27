#pragma once
#include "Command.hpp"
#include "Game.hpp"
namespace oa {
namespace game {
class ExitCommand : public Command {
  void execute();
  Game *game;

 public:
  ExitCommand(Game *);
};
}
}
