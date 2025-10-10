#ifndef BACKGROUND_GAME
#define BACKGROUND_GAME

#include <array>
#include <cstdint>
#include <raylib.h>
#include "../entity/entity.hpp"

class Background {
  private:
    uint8_t count;
    uint16_t x, y = 0;
    uint8_t frameCount = 4;
    uint8_t frameWidth = 16; 
    uint8_t frameHeight = 32;
    Vector2 pos, origin;
    bool rotation, sum;
    Focus f;
    MoveState ms;
    std::array<Texture2D, 2>* imgs;

  public:
    Background(uint16_t x, uint16_t y, bool sum, Focus f, MoveState ms,Vector2 origin, bool rotation, std::array<Texture2D, 2>& imgs);
    void Update();
    void Draw();
};

#endif // !BACKGROUND_GAME
