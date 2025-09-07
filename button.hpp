#ifndef BUTTON
#define BUTTON

#include <raylib.h>

class Button {
  private:
    const char* text;
    int x, y, w, h, fontsize;
    Texture2D& img;

  public:
    Button(int x, int y, int fontsize, const char* text, Texture2D& img);
    void Draw();
    bool isClicked();
    virtual void Action() = 0;
    virtual ~Button() = default;
};

class StartButton : public Button {
  public:
    using Button::Button;
    void Action() override;
};

class ExitButton : public Button {
  public:
    using Button::Button;
    void Action() override;
};

#endif // !BUTTON
