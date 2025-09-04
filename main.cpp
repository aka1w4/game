#include "player.hpp"
#include <memory>
#include <raylib.h>

class Button {
  private:
    const char* text;
    int x, y, w, h, fontsize;
    Texture2D img;

  public:
    Button(int x, int y, int fontsize, const char* text) : x(x), y(y), fontsize(fontsize), text(text) {
      img = LoadTexture("assets/button.png");
      w = img.width;
      h = img.height;
    }

    ~Button() {
      UnloadTexture(img);
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
    Button test;

  public:
    Game(float x, float y, Button b) : test(b) {
      player = std::make_unique<Player>(x, y);
    }
    void Update() {
      player->Update();
    }
    void Drawing() {
      BeginDrawing();
      ClearBackground(WHITE);
      test.Draw();
      player->Drawing();
      if (test.isClicked()) {
        TraceLog(LOG_INFO, "button di click");
      }
      EndDrawing();
    }
};

int main() {
  InitWindow(600, 400, "Test game");
  SetTargetFPS(60);

  Button test = Button(200, 200, 20, "test button");

  Game* g = new Game(100, 100, test);
 
  while (!WindowShouldClose()) {
    g->Update();
    g->Drawing();
  }

  delete g;
  CloseWindow();

  return 0;
}
