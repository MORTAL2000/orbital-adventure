#pragma once
#include "CommandProvider.hpp"
#include "InputListener.hpp"

namespace oa {
namespace game {
class Game;
class GameEventsCommandProvider : public CommandProvider,
                                  public input::InputListener {
  void onKeyDown(int key, int mods);

  Game *game;

 public:
  GameEventsCommandProvider(CommandAcceptor *, Game *);
};
}
}
