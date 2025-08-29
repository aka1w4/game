#include <iostream>
#include <raylib.h>

float width = 16;
float height = 16;

int main() {
  InitWindow(600, 400, "Test game");
  SetTargetFPS(60);

  Texture2D idle = LoadTexture("assets/16x16idle.png");
  Vector2 pos = Vector2{250, 150};
  Rectangle src = Rectangle{0, 0, width, height};
  Rectangle dst = Rectangle{pos.x, pos.y, width*3, height*3};
  Vector2 origin = Vector2{0,0};

  while (!WindowShouldClose()) {
   BeginDrawing();
   ClearBackground(WHITE);
   DrawText("Hello world", 100, 100, 50, BLACK);
   DrawTexturePro(idle, src, dst, origin, 0.0f, WHITE);

   std::cout << "game sedang berjalan: " << std::endl;
   EndDrawing();
  }

  UnloadTexture(idle);
  CloseWindow();

  return 0;
}
