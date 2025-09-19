#ifndef BUTTON
#define BUTTON

#include <functional>
#include <raylib.h>
#include "../db/db.hpp"

enum typeButton {
  ExitGame,
  Exit,
  Start,
  Create,
  Setting,
  Resume,
};

class Button {
  private:
    const char* text;
    int x, y, w, h, fontsize, screenX, screenY;
    Texture2D* img;
    std::function<void()> action;

  public:
    Button(int x, int y, int w, int h, int fontsize, const char* text, Texture2D& img, std::function<void()> action);
    void Draw();
    bool isClicked();
    void Action();
    virtual ~Button() = default;
};

class WorldButton : public Button {
  private:
    WorldInfo wi;

  public:
    WorldButton(int x, int y, int w, int h, int fontsize, Texture2D& img, const WorldInfo& wi, std::function<void(const WorldInfo&)> action) : 
      Button(x, y, w, h, fontsize, wi.name.c_str(), img, [=](){action(wi); }), 
      wi(wi) {}
};
#endif // !BUTTON
