#pragma once
#include "CommandProvider.hpp"
#include "engine/InputListener.hpp"

namespace oa {
namespace game {
class Game;
class GameEventsCommandProvider : public CommandProvider,
                                  public input::InputListener {
  void onKeyDown(int key, int, int mods) override;

  Game *game;

 public:
  GameEventsCommandProvider(CommandAcceptor *, Game *);
};
}
}
