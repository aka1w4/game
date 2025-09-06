#include <memory>
#include <raylib.h>
#include <vector>
#include "player.hpp"
#include "button.hpp"

class Game {
  private:
    std::unique_ptr<Player> player;
    Texture2D buttonTexture;
    std::vector<std::unique_ptr<Button>> buttons;


  public:
    Game(float x, float y) : buttonTexture(LoadTexture("assets/button.png")) {
      player = std::make_unique<Player>(x, y);
      buttons.push_back(std::make_unique<StartButton>(200, 200, 20, "start", buttonTexture));
      buttons.push_back(std::make_unique<ExitButton>(200, 230, 20, "exit", buttonTexture));
      }
    ~Game() {
      UnloadTexture(buttonTexture);
    }
    void Update() {
      player->Update();
    }
    void Drawing() {
      BeginDrawing();
      ClearBackground(WHITE);
      for (auto &b : buttons) {
        b->Draw();
      }
      player->Drawing();
      for (auto &b : buttons) {
        if (b->isClicked()) {
          b->Action();
        }
      }
      EndDrawing();
    }
};

int main() {
  InitWindow(600, 400, "Test game");
  SetTargetFPS(60);

  Game* g = new Game(100, 100);
 
  while (!WindowShouldClose()) {
    g->Update();
    g->Drawing();
  }

  delete g;
  CloseWindow();

  return 0;
}
