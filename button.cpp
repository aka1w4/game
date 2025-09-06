#include <raylib.h>
#include "button.hpp"

Button::Button(int x, int y, int fontsize, const char* text, Texture2D& img) : x(x), y(y), fontsize(fontsize), text(text), img(img) {
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
  TraceLog(LOG_INFO, "button di click");
}

void StartButton::Action() {
  TraceLog(LOG_INFO, "button start di click");
}

void ExitButton::Action() {
  TraceLog(LOG_INFO, "button exit di click");
}
