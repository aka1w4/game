#include <filesystem>
#include <functional>
#include "../../include/raylib/raylib.h"
#include "ui.hpp"

Button::Button(int x, int y, int w, int h, int fontsize, const char* text, Texture2D& img, std::function<void()> action) : x(x), y(y), w(w), h(h), fontsize(fontsize), img(&img), text(text), action(action) {}

void Button::Draw(int offScrollY) {
  // mengambil ukuran lebar dan tinggi layar
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();
  // memperbesar ukuran lebar dan tinggi 
  w2 = w * 2;
  h2 = h * 2;
  int textW = MeasureText(text, fontsize);
  int textH = fontsize;
  // mengatur posisi button
  screenX = (screenWidth - w2) / 2 + x;
  screenY = (screenHeight - h2) / 2 + y + offScrollY;
  // mengatur posisi text di tengah tengah button
  int textX = screenX + (w2 - textW) / 2;
  int textY = screenY + (h2 - textH) / 2;
  // mengecek apakah mouse lagi di arah button
  bool inPos = CheckCollisionPointRec(GetMousePosition(), Rectangle{float(screenX), float(screenY), float(w2), float(h2)});

  Rectangle src = inPos 
    ? Rectangle{0, 31, float(w), float(h)} // jika inPos = true button akan berwarna abu2
    : Rectangle{0, 0, float(w), float(h)}; // jika inPos = false button akan berwarna hitam

  Rectangle dst = Rectangle{float(screenX), float(screenY), float(w2), float(h2)};

  DrawTexturePro(*img, src, dst, Vector2{0,0}, 0.0f, WHITE);
  DrawText(text, textX, textY, fontsize, WHITE);
}

bool Button::isClicked() {
  // mengreturn apakah button di click dan mouse berada di posisi button
  return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
    CheckCollisionPointRec(GetMousePosition(), Rectangle{float(screenX), float(screenY), float(w2), float(h2)});
}

void Button::Action() {
  if(action) action(); // menjalankan action
}

void WorldButton::DrawDelete(int offScrollY) {
  // mengambil ukuran lebar dan tinggi layar
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();
  int h2 = h * 2;

  screenX = (screenWidth) / 2 + x + 190;
  screenY = (screenHeight - h2) / 2 + y + offScrollY;

  DrawTexturePro(*imgicon, Rectangle{16, 48, 16, 16}, Rectangle{(float)screenX, (float)screenY, 50, 50}, Vector2{0,0}, 0.0f, WHITE);
}

bool WorldButton::isClickedDele() {
  // mengreturn apakah button di click dan mouse berada di posisi button
  return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
    CheckCollisionPointRec(GetMousePosition(), Rectangle{float(screenX), float(screenY), float(50), float(50)});
}

void WorldButton::ActionDelete() {
  // menjalankan action
  if (std::filesystem::exists(path)) {
    std::filesystem::remove_all(path);
    if (actionDelete) actionDelete();
  }
}
