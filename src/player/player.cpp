#include "player.hpp"
#include <filesystem>
#include <raylib.h>
#include <fstream>
#include <iostream>

Player::Player(Vector2 pos, Focus f, bool facingright) : pos(pos), f(f), facingright(facingright) {
  img[0] = LoadTexture("assets/16x32idle.png");
  img[1] = LoadTexture("assets/16x32walk.png");

  if (!std::filesystem::exists("bin/player.bin")) {
    std::filesystem::create_directories("bin");
    pos = Vector2{100, 100};
  } else {
    readbinary();
  }
}

Player::~Player() {
  for (auto &i : img) {
    UnloadTexture(i);
  }

  writebinary();
}

void Player::writebinary() {
  std::ofstream out("bin/player.bin", std::ios::binary);
  out.write(reinterpret_cast<char*>(&pos), sizeof(pos));
  out.write(reinterpret_cast<char*>(&f), sizeof(f));
  out.write(reinterpret_cast<char*>(&facingright), sizeof(facingright));
  out.close();
}

void Player::readbinary() {
  std::ifstream in("bin/player.bin", std::ios::binary);
  in.read(reinterpret_cast<char*>(&pos), sizeof(pos));
  in.read(reinterpret_cast<char*>(&f), sizeof(f));
  in.read(reinterpret_cast<char*>(&facingright), sizeof(facingright));
  in.close();

  std::cout << "x: " << pos.x << " y: " << pos.y << std::endl;
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
  int x0 = (count / 8) % frameCount * frameWidth;
  if (facingright) {
    frameWidth = -16;
  } else {
    frameWidth = 16;
  }
   Rectangle src = Rectangle{(float)x0, (float)frameHeight*f, (float)frameWidth, (float)frameHeight};
   Rectangle dst = Rectangle{pos.x, pos.y, (float)frameWidth*3, (float)frameHeight*3};
   Vector2 origin = Vector2{0,0};

   DrawTexturePro(img[ms], src, dst, origin, 0.0f, WHITE);
}
