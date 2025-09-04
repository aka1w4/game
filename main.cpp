#include "player.hpp"
#include <memory>
#include <raylib.h>
#include <vector>

class Button {
  private:
    const char* text;
    int x, y, w, h, fontsize;
    Texture2D& img;

  public:
    Button(int x, int y, int fontsize, const char* text, Texture2D& img) : x(x), y(y), fontsize(fontsize), text(text), img(img) {
      w = img.width;
      h = img.height;
    }

    void Draw() {
      int textW = MeasureText(text, fontsize);
      int textH = fontsize;
      int textX = x + (w - textW) / 2;
      int textY = y + (h - textH) / 2;

      DrawTexture(img, x, y, WHITE);

      DrawText(text, textX, textY, fontsize, WHITE);
    }

    bool isClicked() {
      return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), Rectangle{float(x), float(y), float(w), float(h)});
    }
};

class Game {
  private:
    std::unique_ptr<Player> player;
    Texture2D buttonTexture;
    std::vector<Button> buttons;


  public:
    Game(float x, float y) : buttonTexture(LoadTexture("assets/button.png")) {
      player = std::make_unique<Player>(x, y);
      buttons.push_back(Button(200, 200, 20, "start", buttonTexture));
      buttons.push_back(Button(200, 230, 20, "exit",buttonTexture));
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
        b.Draw();
      }
      player->Drawing();
      for (auto &b : buttons) {
        if (b.isClicked()) {
          TraceLog(LOG_INFO, "button di click");
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
