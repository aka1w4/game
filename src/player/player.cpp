#include "player.hpp"
#include <cstdlib>
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
  Focus fd;
  bool frd = false;
  float dx, dy;
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    dy = -2;
    if (IsKeyDown(KEY_A)) {
      fd = UpLeft;
      dx = -2;
    } else if (IsKeyDown(KEY_D)) {
      fd = UpLeft;
      frd = true;
      dx = 2;
    } else {
      fd = Up;
      dx = 0;
    }
    Move(dx, dy, fd, frd);
  } else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    dy = 2;
    if (IsKeyDown(KEY_A)) {
      fd = DownLeft;
      dx = -2;
    } else if (IsKeyDown(KEY_D)) {
      fd = DownLeft;
      frd = true;
      dx = 2;
    } else {
      fd = Down;
      dx = 0;
    }
    Move(dx, dy, fd, frd);
  } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    dx = 2;
    if (IsKeyDown(KEY_W)) {
      fd = UpLeft;
      frd = true;
      dy = -2;
    } else if (IsKeyDown(KEY_S)) {
      fd = DownLeft;
      frd = true;
      dy = 2;
    } else {
      fd = Left;
      frd = true;
      dy = 0;
    }
    Move(dx, dy, fd, frd);
  } else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    dx = -2;
    if (IsKeyDown(KEY_W)) {
      fd = UpLeft;
      dy = -2;
    } else if (IsKeyDown(KEY_S)) {
      fd = DownLeft;
      dy = 2;
    } else {
      fd = Left;
      dy = 0;
    }
    Move(dx, dy, Left, frd);
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
   Rectangle dst = Rectangle{pos.x, pos.y, (float)frameWidth, (float)frameHeight};
   Vector2 origin = Vector2{0,0};

   DrawTexturePro(img[ms], src, dst, origin, 0.0f, WHITE);
}

void Player::LoadResourcesPlayer() {
  img[0] = LoadTexture("assets/16x32idle.png");
  img[1] = LoadTexture("assets/16x32walk.png");
}

const Rectangle Player::GetRec() {
  return Rectangle{
    pos.x,
    pos.y, 
    (float)std::abs(frameWidth),
    (float)frameHeight,
  };
}

void Player::UpdatePos(Vector2 posNew) {
  pos = posNew;
}
