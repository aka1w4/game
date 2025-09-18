#include <raylib.h>
#include "game.hpp"

int main() {
  InitWindow(GetScreenWidth(), GetScreenHeight(), "Test game");
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);

  Game* g = new Game();
 
  g->Run();

  delete g;
  CloseWindow();

  return 0;
}
