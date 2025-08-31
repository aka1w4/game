#ifndef PLAYER
#define PLAYER

#include <raylib.h>
class Player {
  private:
    Vector2 pos;
    Texture2D img;

  public:
    Player(float x, float y);
    ~Player();
    void Update();
    void Drawing();
};

#endif // !PLAYER
