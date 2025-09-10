#ifndef GAME
#define GAME

#include <raylib.h>
#include <memory>
#include "player.hpp"
#include "button.hpp"

enum GameState {
  MenuState,
  PlayState,
};

class Game {
  private:
    bool quit = false;
    GameState gs = MenuState;
    std::unique_ptr<Player> player = nullptr;
    Texture2D buttonTexture;
    bool pauseGame = false;
    std::unique_ptr<Button> startButton;
    std::unique_ptr<Button> closeButton;
    std::unique_ptr<Button> exitButton;
    std::unique_ptr<Button> resumeButton;

  public:
    Game();
    ~Game();
    void Update();
    void Drawing();
    void Run();
};

#endif // !GAME
