#include "./CommandProvider.hpp"
namespace oa {
namespace game {
void CommandProvider::addCommand(Command *c) { acceptor->addCommand(c); }

void CommandProvider::update(float){};

CommandProvider::CommandProvider(CommandAcceptor *a) : acceptor(a) {}
}
}
