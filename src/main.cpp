#include "../include/raylib/raylib.h"
#include "game.hpp"
#include "gpu_select.hpp"

int main() {
#ifdef __linux__
  enable_nvidia_gpu();
#endif // __linux__
  
  InitWindow(GetScreenWidth(), GetScreenHeight(), "Test game");
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);

  Game* g = new Game();
 
  g->Run();

  delete g;
  CloseWindow();

  return 0;
}
