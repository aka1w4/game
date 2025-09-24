#include "player.hpp"
#include <raylib.h>

Player::Player(Vector2 pos, Focus f, bool facingright) : pos(pos), f(f), facingright(facingright) {}

Player::~Player() {
  for (auto &i : img) {
    UnloadTexture(i);
  }
}

SavePlayer Player::GetPlayer() {
  return SavePlayer{pos, f, facingright};
}

const Vector2& Player::GetPlayerpos() {
  return pos;
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
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    Move(0, -5, Up, false);
  } else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    Move(0, 5, Down, false);
  } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    Move(5, 0, Left, true);
  } else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    Move(-5, 0, Left, false);
  } else {
    ms = isIdle;
  }
}

void Player::Draw() {
  int x0 = (count / 8) % frameCount * frameWidth;
  if (facingright) {
    frameWidth = -16;
  } else {
    frameWidth = 16;
  }
   Rectangle src = Rectangle{(float)x0, (float)frameHeight*f, (float)frameWidth, (float)frameHeight};
   dst = Rectangle{pos.x, pos.y, (float)frameWidth*2, (float)frameHeight*2};
   Vector2 origin = Vector2{0,0};

   DrawTexturePro(img[ms], src, dst, origin, 0.0f, WHITE);
}

void Player::LoadResourcesPlayer() {
  img[0] = LoadTexture("assets/16x32idle.png");
  img[1] = LoadTexture("assets/16x32walk.png");
}

const Rectangle& Player::GetRec() {
  return dst;
}
