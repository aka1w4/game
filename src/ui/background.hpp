#ifndef BACKGROUND_GAME
#define BACKGROUND_GAME

#include <array>
#include <raylib.h>
#include "../player/player.hpp"

class Background {
  private:
    int count, x, y = 0;
    int frameCount = 4;
    int frameWidth = 16; 
    int frameHeight = 32;
    Vector2 pos, origin;
    bool rotation, sum;
    Focus f;
    MoveState ms;
    std::array<Texture2D, 2> imgs;

  public:
    Background(int x, int y, bool sum, Focus f, MoveState ms,Vector2 origin, bool rotation);
    ~Background();
    void Update();
    void Draw();
};

#endif // !BACKGROUND_GAME
