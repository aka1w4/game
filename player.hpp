#ifndef PLAYER
#define PLAYER

#include <array>
#include <raylib.h>

enum Focus {
  Down,
  Left = 2, 
  Up = 4,
};

enum MoveState {
  isIdle,
  isWalk,
};

class Player {
  private:
    Vector2 pos;
    std::array<Texture2D, 2> img;
    unsigned int count;
    Focus f = Down;
    MoveState ms;
    bool facingright; 

  public:
    Player(float x, float y);
    ~Player();
    void Update();
    void Drawing();
    void Move(float dx, float dy, Focus df, bool right);
};

#endif // !PLAYER
