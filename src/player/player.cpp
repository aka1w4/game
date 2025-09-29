#include "player.hpp"
#include <array>
#include <cstdlib>
#include <raylib.h>

Player::Player(Vector2 pos, Focus f, bool facingright, std::array<Texture2D, 2>& imgs) : pos(pos), f(f), facingright(facingright), imgs(&imgs) {}

SavePlayer Player::GetPlayer() {
  return SavePlayer{pos, f, facingright};
}

const Vector2& Player::GetPlayerpos() {
  return pos;
}

void Player::Move(float dx, float dy, Focus newFocus, bool right) {
  // memperiksa dx dan dy yang tidak boleh sama dengan 0
  if (dx != 0 || dy != 0) {
    // memperiksa status move jika isIdle 
    if (ms == isIdle) {
      ms = isWalk; // mengubah status move player ke isWalk
    }

    pos.x += dx;          // update posisi x dari dx
    pos.y += dy;          // update posisi y dari dy
    f = newFocus;         // update arah f dari newFocus
    facingright = right;  // update facingright dari right
  } else {
    ms = isIdle;          // mengubah status move ke isIdle 
  }
}

void Player::Update() {
  count++;            // menambahkan count
  Focus newFocus;     // focus sementara untuk menetukan pergerakan 
  bool right = false; // apakah player sedang hadapkanan
  float dx, dy;       // perubahan posisi player di sumbu x dan y 
  
  // input handle untuk pergerakan
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {    // gerak ke atas 
    dy = -2;
    if (IsKeyDown(KEY_A)) {                       // serong kiri-atas
      right = UpLeft;
      dx = -2;
    } else if (IsKeyDown(KEY_D)) {                // serong kanan-atas
      newFocus = UpLeft;
      right = true;
      dx = 2;
    } else {
      newFocus = Up;
      dx = 0;
    }
    Move(dx, dy, newFocus, right);
  } else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) { // gerak ke bawah
    dy = 2;
    if (IsKeyDown(KEY_A)) {                             // serong ke kiri-bawah
      newFocus = DownLeft;
      dx = -2;
    } else if (IsKeyDown(KEY_D)) {                      // serong ke kanan-bawah
      newFocus = DownLeft;
      right = true;
      dx = 2;
    } else {
      newFocus = Down;
      dx = 0;
    }
    Move(dx, dy, newFocus, right);
  } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { // gerak ke kanan
    dx = 2;
    if (IsKeyDown(KEY_W)) {                              // serong ke atas-kanan 
      newFocus = UpLeft;
      right = true;
      dy = -2;
    } else if (IsKeyDown(KEY_S)) {                       // serong ke bawah-kanan
      newFocus = DownLeft;
      right = true;
      dy = 2;
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
      dy = -2;
    } else if (IsKeyDown(KEY_S)) {                      // serong atas-kanan
      newFocus = DownLeft;
      dy = 2;
    } else {
      newFocus = Left;
      dy = 0;
    }
    Move(dx, dy, newFocus, right);
  } else {
    ms = isIdle;    // tidak ada input masuk
  }
}

void Player::Draw() {
  // hitung posisi x frame animasi 
  int x0 = (count / 8) % frameCount * frameWidth;

  // mengecek nilai facingright untuk mengubah nilai frameWidth
  if (facingright) {
    frameWidth = -16;
  } else {
    frameWidth = 16;
  }


  Rectangle src = Rectangle{
    (float)x0,             // posisi x frame
    (float)frameHeight*f,  // posisi y frame
    (float)frameWidth,     // lebar 1 frame
    (float)frameHeight     // tinggi 1 frame 
  };
  Rectangle dst = Rectangle{
    pos.x,              // posisi x di layar
    pos.y,              // posisi y di layar 
    (float)frameWidth,  // lebar saat digambar
    (float)frameHeight  // tinggi saat digambar 
  };
  Vector2 origin = Vector2{0,0}; // titik rotasi / scale

  DrawTexturePro((*imgs)[ms], src, dst, origin, 0.0f, WHITE);
}

const Rectangle Player::GetRec() {
  return Rectangle{
    pos.x,                        // posisi x saat ini
    pos.y,                        // posisi y saat ini
    (float)std::abs(frameWidth),  // lebar frame
    (float)frameHeight,           // tinggi frame
  };
}

void Player::UpdatePos(Vector2 posNew) {
  // menyimpan posisi baru 
  pos = posNew;
}
