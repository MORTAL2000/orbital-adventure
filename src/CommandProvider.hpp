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
  virtual void update(float t);
  CommandProvider(CommandAcceptor *);
  virtual ~CommandProvider(){};
};
}
}
