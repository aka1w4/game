#ifndef PLAYER
#define PLAYER

#include <array>
#include <raylib.h>

enum Focus {
  Down,
  DownLeft,
  Left,
  UpLeft,
  Up,
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
    std::array<Texture2D, 2>* imgs;
    unsigned int count;
    Focus f = Down;
    MoveState ms;
    bool facingright; 
    int frameCount = 4;
    int frameWidth = 16;
    int frameHeight = 32;

  public:
    Player(Vector2 pos, Focus f, bool facingright, std::array<Texture2D, 2>& imgs);
    void Update();
    void Draw();
    void Move(float dx, float dy, Focus df, bool right);
    SavePlayer GetPlayer();
    const Vector2& GetPlayerpos();
    const Rectangle GetRec();
    void UpdatePos(Vector2 posNew);
};

#endif // !PLAYER
