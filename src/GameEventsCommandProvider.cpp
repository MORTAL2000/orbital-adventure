#include "GameEventsCommandProvider.hpp"
#include "Game.hpp"
#include "ExitCommand.hpp"

namespace oa {
namespace game {
GameEventsCommandProvider::GameEventsCommandProvider(CommandAcceptor* acceptor,
                                                     Game* game)
    : CommandProvider(acceptor), game(game) {}

void GameEventsCommandProvider::onKeyDown(int key, int) {
  std::cout << "on key down\n";
  switch (key) {
    case GLFW_KEY_ESCAPE:
      addCommand(new ExitCommand(game));
      return;
  }
}
}
}
