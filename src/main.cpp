#include "Game.hpp"


using  oa::game::Game;

int main(){

  Game game;
  game.init();
  game.mainLoop();

  return 0;
}
