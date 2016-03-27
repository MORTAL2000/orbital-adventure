#include "ExitCommand.hpp"
#include <iostream>
namespace oa {
namespace game {
ExitCommand::ExitCommand(Game *g) : game(g) {}
void ExitCommand::execute() { game->stopGame(); }
}
}
