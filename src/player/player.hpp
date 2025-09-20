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

struct SavePlayer {
  Vector2 pos;
  Focus f;
  bool facingright;
};

class Player {
  private:
    Vector2 pos;
    std::array<Texture2D, 2> img;
    unsigned int count;
    Focus f = Down;
    MoveState ms;
    bool facingright; 
    int frameCount = 4;
    int frameWidth = 16;
    int frameHeight = 32;

  public:
    Player(Vector2 pos, Focus f, bool facingright);
    ~Player();
    void Update();
    void Draw();
    void Move(float dx, float dy, Focus df, bool right);
    SavePlayer GetPlayer();
    const Vector2& GetPlayerpos();
};

#endif // !PLAYER
