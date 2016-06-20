#include "Game.hpp"
#include <iostream>
#include "ExitCommand.hpp"
#include "GameEventsCommandProvider.hpp"

namespace oa {
namespace game {
GameEventsCommandProvider::GameEventsCommandProvider(CommandAcceptor* acceptor,
                                                     Game* game)
    : CommandProvider(acceptor), game(game) {
  std::cout << "GECP\n";
}

void GameEventsCommandProvider::onKeyDown(int key, int, int) {
  std::cout << "on key down\n";
  switch (key) {
    case GLFW_KEY_ESCAPE:
      addCommand(new ExitCommand(game));
      return;
  }
}
}
}
