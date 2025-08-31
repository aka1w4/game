#include "player.hpp"
#include <memory>
#include <raylib.h>

class Game {
  private:
    std::unique_ptr<Player> player;

  public:
    Game(float x, float y) {
      player = std::make_unique<Player>(x, y);
    }
    void Update() {
      player->Update();
    }
    void Drawing() {
      BeginDrawing();
      ClearBackground(WHITE);
      DrawText("Hello world", 100, 100, 50, BLACK);
      player->Drawing();
      EndDrawing();
    }
};

int main() {
  InitWindow(600, 400, "Test game");
  SetTargetFPS(60);

  Game g = Game(100, 100);
 
  while (!WindowShouldClose()) {
    g.Update();
    g.Drawing();
  }

  CloseWindow();

  return 0;
}
