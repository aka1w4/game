#include <iostream>
#include <raylib.h>

float width = 16;
float height = 16;
Vector2 pos = Vector2{250, 150};

void Update() {
  if (IsKeyDown(KEY_W)) {
    pos.y -= 5;
  } else if (IsKeyDown(KEY_S)) {
    pos.y += 5;
  } else if (IsKeyDown(KEY_D)) {
    pos.x += 5;
  } else if (IsKeyDown(KEY_A)) {
    pos.x -= 5;
  }
}

void Drawing(Texture2D img) {
   BeginDrawing();
   ClearBackground(WHITE);
   Rectangle src = Rectangle{0, 0, width, height};
   Rectangle dst = Rectangle{pos.x, pos.y, width*3, height*3};
   Vector2 origin = Vector2{0,0};

   DrawText("Hello world", 100, 100, 50, BLACK);
   DrawTexturePro(img, src, dst, origin, 0.0f, WHITE);

   std::cout << "game sedang berjalan: " << std::endl;
   EndDrawing();
}

int main() {
  InitWindow(600, 400, "Test game");
  SetTargetFPS(60);

  Texture2D idle = LoadTexture("assets/16x16idle.png");
  
  while (!WindowShouldClose()) {
    Update();
    Drawing(idle);
  }

  UnloadTexture(idle);
  CloseWindow();

  return 0;
}
