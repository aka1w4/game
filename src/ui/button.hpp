#ifndef BUTTON
#define BUTTON

#include <functional>
#include <raylib.h>

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
    int x, y, w, h, fontsize;
    Texture2D* img;
    std::function<void()> action;

  public:
    Button(int x, int y, int fontsize, const char* text, Texture2D& img, std::function<void()> action);
    void Draw();
    bool isClicked();
    void Action();
    virtual ~Button() = default;
};

#endif // !BUTTON
