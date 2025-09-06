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
    virtual void Action();
};

#endif // !BUTTON
