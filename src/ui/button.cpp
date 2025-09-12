#include <functional>
#include <raylib.h>
#include "button.hpp"

Button::Button(int x, int y, int fontsize, const char* text, Texture2D& img, std::function<void()> action) : x(x), y(y), fontsize(fontsize), text(text), img(img), action(action){
  w = img.width;
  h = img.height;
}

void Button::Draw() {
  int textW = MeasureText(text, fontsize);
  int textH = fontsize;
  int textX = x + (w - textW) / 2;
  int textY = y + (h - textH) / 2;

  DrawTexture(img, x, y, WHITE);
  DrawText(text, textX, textY, fontsize, WHITE);
}

bool Button::isClicked() {
  return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
    CheckCollisionPointRec(GetMousePosition(), Rectangle{float(x), float(y), float(w), float(h)});
}

void Button::Action() {
  if(action) action();
  TraceLog(LOG_INFO, "button di click");
}
