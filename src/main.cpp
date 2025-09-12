#include <raylib.h>
#include "game.hpp"

int main() {
  InitWindow(600, 400, "Test game");
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);

  Game* g = new Game();
 
  g->Run();

  delete g;
  CloseWindow();

  return 0;
}
