#pragma once
#include "./CommandAcceptor.hpp"
namespace oa {
namespace game {
class CommandProvider {
 private:
  CommandAcceptor *acceptor;

 protected:
  void addCommand(Command *);

 public:
  CommandProvider(CommandAcceptor *);
  virtual ~CommandProvider(){};
};
}
}
