#ifndef GAME
#define GAME

#include <raylib.h>
#include <memory>
#include <vector>
#include "ui/button.hpp"
#include "db/db.hpp"
#include "world/world.hpp"

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
    std::unique_ptr<World> world = nullptr;
    Texture2D buttonTexture;
    Texture2D inputTextTexture;
    bool pauseGame = false;
    readWorldlist ws;
    int scrollofset = 0;
    std::vector<std::unique_ptr<WorldButton>> wbs;
    std::unique_ptr<Button> startButton;
    std::unique_ptr<Button> closeButton;
    std::unique_ptr<Button> exitButton;
    std::unique_ptr<Button> resumeButton;
    std::unique_ptr<Button> BackButton;
    std::unique_ptr<Button> NewWorldButton;
    std::unique_ptr<NewWorld> newworld;

  public:
    Game();
    ~Game();
    void Update();
    void Drawing();
    void Run();
};

#endif // !GAME
