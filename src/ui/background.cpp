#include "raylib/raylib.h"
#include "ui.hpp"

void Background::Update() {
  count++;
  if (sum) {
    pos.x++;
    pos.y++;
  } else {
    pos.x--;
    pos.y--;
  }

  if (pos.x >= 1400 || pos.x <= -20) {
    pos.x = x;
    pos.y = y;
  } else if (pos.y >= 850 || pos.y <= -20) {
    pos.y = y;
    pos.x = x;
  }
}
 
void Background::Draw() {
  int x0 = (count / 8) % frameCount * frameWidth;

  Rectangle src = Rectangle{(float)x0, (float)frameHeight*(float)f, (float)frameWidth, (float)frameHeight};
  Rectangle dst = Rectangle{pos.x, pos.y, (float)frameWidth*3, (float)frameHeight*3};
  
  if (rotation) {
    DrawTexturePro((*imgs)[ms], src, dst, origin, 1.0f + count, WHITE);
  } else {
    DrawTexturePro((*imgs)[ms], src, dst, origin, 0.0f, WHITE);
  }
}
