#include "player.hpp"
#include <iostream>
#include <raylib.h>

float width = 16;
float height = 16;

Player::Player(float x, float y) : pos(Vector2{x, y}) {
   img = LoadTexture("assets/16x16idle.png");
}

Player::~Player() {
  UnloadTexture(img);
}

void Player::Update() {
  if (IsKeyDown(KEY_W)) {
    pos.y -= 5;
  } else if (IsKeyDown(KEY_S)) {
    pos.y += 5;
  } else if (IsKeyDown(KEY_D)) {
    pos.x += 5;
  } else if (IsKeyDown(KEY_A)) {
    pos.x -= 5;
  }
}

void Player::Drawing() {
   Rectangle src = Rectangle{0, 0, width, height};
   Rectangle dst = Rectangle{pos.x, pos.y, width*3, height*3};
   Vector2 origin = Vector2{0,0};

   DrawTexturePro(img, src, dst, origin, 0.0f, WHITE);

   std::cout << "game sedang berjalan: " << std::endl;
}
