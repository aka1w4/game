#include <iostream>
#include <raylib.h>

int main() {
  InitWindow(600, 400, "Test game");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
   BeginDrawing();
   ClearBackground(WHITE);
   DrawText("Hello world", 100, 100, 50, BLACK);

   std::cout << "game sedang berjalan" << std::endl;

   EndDrawing();
  }

  CloseWindow();

  return 0;
}
