#ifndef TEXTINPUT
#define TEXTINPUT

#include <raylib.h>
#include <string>

class Textinput {
  private:
    int x, y, w, h, fontsize;
    std::string text;
    bool inTextinput = false;
    Texture2D* img;

  public:
    Textinput(int x, int y, int w, int h, int fontsize, Texture2D& img);
    void checkPos();
    void Draw();
    bool inTextInput();
    void EditInputText();
    std::string GetText();
    void ClearText();
};

#endif // !TEXTINPUT
