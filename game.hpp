#ifndef GAME
#define GAME

#include <raylib.h>
#include <memory>
#include "player.hpp"
#include "button.hpp"
#include <vector>

class Game {
  private:
    bool quit = false;
    std::unique_ptr<Player> player;
    Texture2D buttonTexture;
    std::vector<std::unique_ptr<Button>> buttons;


  public:
    Game(float x, float y);
    ~Game();
    void Update();
    void Drawing();
    void Run();
};

#endif // !GAME
