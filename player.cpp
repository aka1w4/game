#include "player.hpp"
#include <raylib.h>

float width = 16;
float height = 32;
int frameCount = 4;

Player::Player(float x, float y) : pos(Vector2{x, y}) {
   img[0] = LoadTexture("assets/16x32idle.png");
   img[1] = LoadTexture("assets/16x32walk.png");
}

Player::~Player() {
  for (auto &i : img) {
    UnloadTexture(i);
  }
}

void Player::Move(float dx, float dy, Focus df, bool right) {
  if (dx != 0 || dy != 0) {
    if (ms == isIdle) {
      ms = isWalk;
    }

    pos.x += dx;
    pos.y += dy;
    f = df;
    facingright = right;
  } else {
    ms = isIdle;
  }
}

void Player::Update() {
  count++;
  if (IsKeyDown(KEY_W)) {
    Move(0, -5, Up, false);
  } else if (IsKeyDown(KEY_S)) {
    Move(0, 5, Down, false);
  } else if (IsKeyDown(KEY_D)) {
    Move(5, 0, Left, true);
  } else if (IsKeyDown(KEY_A)) {
    Move(-5, 0, Left, false);
  } else {
    ms = isIdle;
  }
}

void Player::Drawing() {
  int x0 = (count / 8) % frameCount * width;
  if (facingright) {
    width = -16;
  } else {
    width = 16;
  }
   Rectangle src = Rectangle{(float)x0, height*f, width, height};
   Rectangle dst = Rectangle{pos.x, pos.y, width*3, height*3};
   Vector2 origin = Vector2{0,0};

   DrawTexturePro(img[ms], src, dst, origin, 0.0f, WHITE);
}
