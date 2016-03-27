#include "./CommandProvider.hpp"
namespace oa {
namespace game {
void CommandProvider::addCommand(Command *c) { acceptor->addCommand(c); }

CommandProvider::CommandProvider(CommandAcceptor *a) : acceptor(a) {}
}
}
