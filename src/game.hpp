#ifndef GAME
#define GAME

#include <array>
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
    Texture2D buttonTexture, inputTextTexture, iconTexture, healthTexture;
    bool pauseGame = false;
    readWorldlist ws;
    int scrollofset = 0;
    std::vector<std::unique_ptr<WorldButton>> wbs;
    Button startButton, closeButton, exitButton, resumeButton, BackButton, NewWorldButton;
    std::unique_ptr<NewWorld> newworld;
    std::array<Texture2D, 2> playerTextures = {
      LoadTexture("assets/16x32idle.png"),
      LoadTexture("assets/16x32walk.png"),
    };
    std::array<Background, 3> bs = {
      Background(800, 800, false, Down, isIdle, Vector2{0, 0}, true, playerTextures),
      Background(-10, -10, true, Left, isWalk, Vector2{50, 50}, true, playerTextures),
      Background(500, -10, true, Up, isWalk, Vector2{0, 0}, false, playerTextures),
    };

  public:
    Game();
    ~Game();
    void Update();
    void Drawing();
    void Run();
    void CreateButtonReadWorld();
};

#endif // !GAME
