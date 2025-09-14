#ifndef GAME
#define GAME

#include <functional>
#include <raylib.h>
#include <memory>
#include <chrono>
#include "player/player.hpp"
#include "ui/button.hpp"

enum GameState {
  MenuState,
  PlayState,
  WorldListState,
  CreateWorldState,
};

class Game {
  private:
    bool quit = false;
    GameState gs = MenuState;
    std::unique_ptr<Player> player = nullptr;
    Texture2D buttonTexture;
    bool pauseGame = false;
    std::chrono::time_point<std::chrono::steady_clock> lastSave;
    std::unique_ptr<Button> startButton;
    std::unique_ptr<Button> closeButton;
    std::unique_ptr<Button> exitButton;
    std::unique_ptr<Button> resumeButton;
    std::unique_ptr<Button> BackButton;
    std::unique_ptr<Button> NewWorldButton;
    std::unique_ptr<Button> CreateWorldButton;

  public:
    Game();
    ~Game();
    void Update();
    void Drawing();
    void Run();
    std::unique_ptr<Button> MakeButton(int x, int y, int width, int height, int fontsize, const char* text, std::function<void()> action);
};

#endif // !GAME
