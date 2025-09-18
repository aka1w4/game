#include <functional>
#include <raylib.h>
#include "button.hpp"

Button::Button(int x, int y, int w, int h, int fontsize, const char* text, Texture2D& img, std::function<void()> action) : x(x), y(y), w(w), h(h), fontsize(fontsize), img(&img), text(text), action(action){
}

void Button::Draw() {
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();
  int textW = MeasureText(text, fontsize);
  int textH = fontsize;
  screenX = (screenWidth - w) / 2 + x;
  screenY = (screenHeight - h) / 2 + y;
  int textX = screenX + (w - textW) / 2;
  int textY = screenY + (h - textH) / 2;

  bool inPos = CheckCollisionPointRec(GetMousePosition(), Rectangle{float(screenX), float(screenY), float(w), float(h)});
  if (inPos) {
    DrawTextureRec(*img, Rectangle{0, 31, float(w), float(h)}, Vector2{float(screenX), float(screenY)}, WHITE);
  } else {
    DrawTextureRec(*img, Rectangle{0, 0, float(w), float(h)}, Vector2{float(screenX), float(screenY)}, WHITE);
  }

  //DrawTextureRec(*img, Rectangle{0, 31, float(w), float(h)}, Vector2{float(x), float(y)}, WHITE);
  DrawText(text, textX, textY, fontsize, WHITE);
}

bool Button::isClicked() {
  return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
    CheckCollisionPointRec(GetMousePosition(), Rectangle{float(screenX), float(screenY), float(w), float(h)});
}

void Button::Action() {
  if(action) action();
  TraceLog(LOG_INFO, "button di click");
}
