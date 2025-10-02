#ifndef ENTITY_PLAYER
#define ENTITY_PLAYER

#include <raylib.h>
#include <array>
#include <boost/uuid/uuid.hpp>

/// @brief Arah hadap player (digunakan untuk animasi atau pergerakan)
enum Focus {
  Down,
  DownLeft,
  Left,
  UpLeft,
  Up,
};

/// @brief Status gerak entity
enum MoveState {
  isIdle,
  isWalk,
};

/// @brief data yang disave/diload 
struct SaveEntity {
  Vector2 pos;
  Focus f;
  bool facingright;
  int health, maxHealth;
  boost::uuids::uuid uuid;
};

struct Entity {
  Vector2 pos;                      // posisi saat ini
  boost::uuids::uuid uuid;          // identitas entity
  int health, maxHealth;            // darah saat ini dan maksumal darah
  Focus f = Down;                   // Arah player saat ini
  bool facingright;                 // arah hadap ke kanan
  MoveState ms;                     // status gerak player saat ini
  std::array<Texture2D, 2>* imgs;   // pointer array sprite image Entity
  Texture2D* healthimg;             // texture image health
  unsigned int count;               // pinghitungan frame
  int frameCount;                   // jumlah frame animasi
  int frameWidth;                   // lebar sprite per frame
  int frameHeight;                  // tinggi sprite per frame
};

#endif // !ENTITY_PLAYER
