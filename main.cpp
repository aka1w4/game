#include <raylib.h>
#include "game.hpp"

int main() {
  InitWindow(600, 400, "Test game");
  SetTargetFPS(60);

  Game* g = new Game(100, 100);
 
  g->Run();

  delete g;
  CloseWindow();

  return 0;
}
