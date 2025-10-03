#include "entity.hpp"
#include <raylib.h>

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
    (float)x0,             // posisi x frame
    (float)e.frameHeight*(float)e.f,  // posisi y frame
    (float)e.frameWidth,     // lebar 1 frame
    (float)e.frameHeight     // tinggi 1 frame 
  };
  Rectangle dst = Rectangle{
    e.pos.x,              // posisi x di layar
    e.pos.y,              // posisi y di layar 
    (float)e.frameWidth,  // lebar saat digambar
    (float)e.frameHeight  // tinggi saat digambar 
  };
  Vector2 origin = Vector2{0,0}; // titik rotasi / scale

  DrawTexturePro((*e.imgs)[e.ms], src, dst, origin, 0.0f, WHITE);
}

void Enemy::Update() {
  e.count++;
}

SaveEntity Enemy::GetEntity() {
  return SaveEntity{e.pos, e.f, e.facingright, health, maxHealth, e.uuid};
}
