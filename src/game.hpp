#ifndef GAME
#define GAME

#include <raylib.h>
#include <memory>
#include <vector>
#include "ui/background.hpp"
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
    Background b1, b2, b3;
    bool pauseGame = false;
    readWorldlist ws;
    int scrollofset = 0;
    std::vector<std::unique_ptr<WorldButton>> wbs;
    Button startButton, closeButton, exitButton, resumeButton, BackButton, NewWorldButton;
    std::unique_ptr<NewWorld> newworld;

  public:
    Game();
    ~Game();
    void Update();
    void Drawing();
    void Run();
    void CreateButtonReadWorld();
};

#endif // !GAME
