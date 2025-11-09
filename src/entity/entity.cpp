#include "entity.hpp"
#include "../../include/raylib/raylib.h"
#include "../../include/raylib/raymath.h"

void Enemy::Draw() {
  // hitung posisi x frame animasi
  int x0 = (e.count / 8) % e.frameCount * e.frameWidth;

  // mengecek nilai facingright untuk mengubah nilai frameWidth
  if (e.facingright) {
    e.frameWidth = -16;
  } else {
    e.frameWidth = 16;
  }

  Rectangle src = Rectangle{
      (float)x0,                         // posisi x frame
      (float)e.frameHeight * (float)e.f, // posisi y frame
      (float)e.frameWidth,               // lebar 1 frame
      (float)e.frameHeight               // tinggi 1 frame
  };
  Rectangle dst = Rectangle{
      e.pos.x,             // posisi x di layar
      e.pos.y,             // posisi y di layar
      (float)e.frameWidth, // lebar saat digambar
      (float)e.frameHeight // tinggi saat digambar
  };
  Vector2 origin = Vector2{0, 0}; // titik rotasi / scale

  DrawTexturePro((*e.imgs)[e.ms], src, dst, origin, 0.0f, WHITE);
}

void Enemy::Update() { e.count++; }

SaveEntity Enemy::GetEntity() {
  return SaveEntity{e.pos,     e.f,    e.facingright, health,
                    maxHealth, e.uuid, e.count};
}

Vector2 &Enemy::GetPosEntity() { return e.pos; }

void Enemy::Idle() { e.ms = isIdle; }

void Enemy::FollowPlayer(Vector2 &posPlayer) {
  e.ms = isWalk;

  Vector2 direction =
      Vector2Subtract(posPlayer, e.pos); // arah player ke entity
  float len =
      Vector2Distance(e.pos, posPlayer); // jarak antar entity dengan player

  // memberhentikan entity
  if (len <= 10.0f) {
    e.ms = isIdle;
    return;
  }

  float speed = 1.2f;                      // speed entity
  direction = Vector2Normalize(direction); // normalisasi arah
  e.pos =
      Vector2Add(e.pos, Vector2Scale(direction, speed)); // menentukan posisi

  e.facingright = (direction.x > 0.0f); // menentukan flip entity

  // menentukan menghadap kemana
  if (std::fabs(direction.x) > std::fabs(direction.y)) {
    e.f = Left;
  } else {
    if (direction.y > 0)
      e.f = DownLeft;
    else
      e.f = UpLeft;
  }
}
