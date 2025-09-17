#include <iostream>
#include <raylib.h>
#include <string>
#include "textinput.hpp"

Textinput::Textinput(int x, int y, int w, int h, int fontsize,Texture2D& img) : x(x), y(y), w(w), h(h), fontsize(fontsize), img(&img) {}

void Textinput::Draw() {
  int maxWidth = w - 20;
  const char* display = text.c_str();
  while (MeasureText(display, fontsize) > maxWidth && *display) {
    display++;
  }
  int textW = MeasureText(text.c_str(), fontsize);
  int textH = fontsize;
  int textX = x + 10;
  int textY = y + (h - textH) / 2;

  DrawTexture(*img, x, y, WHITE);
  if (text.size() >= 32) {
    DrawText(display, textX, textY, fontsize, RED);
  } else {
    DrawText(display, textX, textY, fontsize, WHITE);
  }
}

void Textinput::checkPos() {
  if ( IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), Rectangle{float(x), float(y), float(w+10), float(h+10)})) {
    inTextinput = true;
  }
}

bool Textinput::inTextInput() {
  return inTextinput;
}

void Textinput::EditInputText() {
  int key = GetCharPressed();
  while (key > 0) {
    if ((key >= 32) && (key <= 125) && (text.size() < 32)) {
      text.push_back((char)key);
    }
    std::cout << "Char pressed: " << (char)key << " (" << key << ")\n";
    key = GetCharPressed();
  }

  if ((IsKeyPressed(KEY_BACKSPACE)) && !text.empty()) {
    text.pop_back();
  }

  if (IsKeyPressed(KEY_ESCAPE)) {
    inTextinput = false;
  }
}

std::string Textinput::GetText() {
  return text;
}

void Textinput::ClearText() {
  text.clear();
}
