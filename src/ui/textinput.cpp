#include "../../include/raylib/raylib.h"
#include "ui.hpp"
#include <string>

void Textinput::Draw() {
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();
  int w2 = w * 2;
  int h2 = h * 2;
  int maxWidth = w2 - 20;
  const char *display = text.c_str();
  while (MeasureText(display, fontsize) > maxWidth && *display) {
    display++;
  }
  screenX = (screenWidth - w2) / 2 + x;
  screenY = (screenHeight - h2) / 2 + y;
  int textW = MeasureText(text.c_str(), fontsize);
  int textH = fontsize;
  int textX = screenX + 10;
  int textY = screenY + (h2 - textH) / 2;

  Rectangle src = Rectangle{0, 0, float(w), float(h)};
  Rectangle dst =
      Rectangle{float(screenX), float(screenY), float(w2), float(h2)};
  DrawTexturePro(*img, src, dst, Vector2{0, 0}, 0.0f, WHITE);
  if (text.size() >= 32) {
    DrawText(display, textX, textY, fontsize, RED);
  } else {
    DrawText(display, textX, textY, fontsize, WHITE);
  }
}

void Textinput::checkPos() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      CheckCollisionPointRec(GetMousePosition(),
                             Rectangle{float(screenX), float(screenY),
                                       float(w * 2), float(h * 2)})) {
    inTextinput = true;
  }
}

bool Textinput::inTextInput() { return inTextinput; }

void Textinput::EditInputText() {
  int key = GetCharPressed();
  while (key > 0) {
    if ((key >= 32) && (key <= 125) && (text.size() < 32)) {
      text.push_back((char)key);
    }
    key = GetCharPressed();
  }

  if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) &&
      !text.empty()) {
    text.pop_back();
  }

  if (IsKeyPressed(KEY_ESCAPE)) {
    inTextinput = false;
  }
}

std::string Textinput::GetText() { return text; }

void Textinput::ClearText() { text.clear(); }
