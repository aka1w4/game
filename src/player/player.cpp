#include "player.hpp"
#include "../entity/entity.hpp"
#include <cstdlib>
#include <raylib.h>

SaveEntity Player::GetPlayer() {
  return SaveEntity{e.pos, e.f, e.facingright, health, maxHealth, e.uuid};
}

const Vector2& Player::GetPlayerpos() {
  return e.pos;
}

void Player::Move(float dx, float dy, Focus newFocus, bool right) {
  // memperiksa dx dan dy yang tidak boleh sama dengan 0
  if (dx != 0 || dy != 0) {
    // memperiksa status move jika isIdle 
    if (e.ms == isIdle) {
      e.ms = isWalk; // mengubah status move player ke isWalk
    }

    e.pos.x += dx;          // update posisi x dari dx
    e.pos.y += dy;          // update posisi y dari dy
    e.f = newFocus;         // update arah f dari newFocus
    e.facingright = right;  // update facingright dari right
  } else {
    e.ms = isIdle;          // mengubah status move ke isIdle 
  }
}

void Player::Update() {
  e.count++;            // menambahkan count
  Focus newFocus;     // focus sementara untuk menetukan pergerakan 
  bool right = false; // apakah player sedang hadapkanan
  float dx, dy;       // perubahan posisi player di sumbu x dan y 
  
  // input handle untuk pergerakan
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {    // gerak ke atas 
    dy = -1.4;
    if (IsKeyDown(KEY_A)) {                       // serong kiri-atas
      newFocus = UpLeft;
      dx = -1.4;
    } else if (IsKeyDown(KEY_D)) {                // serong kanan-atas
      newFocus = UpLeft;
      right = true;
      dx = 1.4;
    } else {
      newFocus = Up;
      dx = 0;
    }
    Move(dx, dy, newFocus, right);
  } else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) { // gerak ke bawah
    dy = 1.4;
    if (IsKeyDown(KEY_A)) {                             // serong ke kiri-bawah
      newFocus = DownLeft;
      dx = -1.4;
    } else if (IsKeyDown(KEY_D)) {                      // serong ke kanan-bawah
      newFocus = DownLeft;
      right = true;
      dx = 1.4;
    } else {
      newFocus = Down;
      dx = 0;
    }
    Move(dx, dy, newFocus, right);
  } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { // gerak ke kanan
    dx = 1.4;
    if (IsKeyDown(KEY_W)) {                              // serong ke atas-kanan 
      newFocus = UpLeft;
      right = true;
      dy = -1.4;
    } else if (IsKeyDown(KEY_S)) {                       // serong ke bawah-kanan
      newFocus = DownLeft;
      right = true;
      dy = 1.4;
    } else {
      newFocus = Left;
      right = true;
      dy = 0;
    }
    Move(dx, dy, newFocus, right);
  } else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) { // gerak ke kiri
    dx = -2;
    if (IsKeyDown(KEY_W)) {                             // serong atas-kiri
      newFocus = UpLeft;
      dy = -1.4;
    } else if (IsKeyDown(KEY_S)) {                      // serong atas-kanan
      newFocus = DownLeft;
      dy = 1.4;
    } else {
      newFocus = Left;
      dy = 0;
    }
    Move(dx, dy, newFocus, right);
  } else {
    e.ms = isIdle;    // tidak ada input masuk
  }
}

void Player::Draw() {
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

const Rectangle Player::GetRec() {
  return Rectangle{
    e.pos.x,                        // posisi x saat ini
    e.pos.y,                        // posisi y saat ini
    (float)std::abs(e.frameWidth),  // lebar frame
    (float)e.frameHeight,           // tinggi frame
  };
}

void Player::UpdatePos(Vector2 posNew) {
  // menyimpan posisi baru 
  e.pos = posNew;
}

void Player::DrawHeart() {
  for (int i=0; i < maxHealth/2; i++) {
    int screenX = i * 33; // menentukan posisi screen x
    int hpIndex = i * 2;  // menentukan nilai awal dari hp(2 hp)
    if (health > hpIndex + 1) {
      DrawTexturePro(*healthimg, Rectangle{0, 0, 11, 11}, Rectangle{(float)screenX, 0, 33, 33}, Vector2{0,0}, 0.0f, WHITE); // full health
    } else if (health == hpIndex + 1) {
      DrawTexturePro(*healthimg, Rectangle{11, 0, 11, 11}, Rectangle{(float)screenX, 0, 33, 33}, Vector2{0,0}, 0.0f, WHITE); // half health
    } else {
      DrawTexturePro(*healthimg, Rectangle{22, 0, 11, 11}, Rectangle{(float)screenX, 0, 33, 33}, Vector2{0,0}, 0.0f, WHITE); // empty health
    }
  }
}
