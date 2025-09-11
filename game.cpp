#include <cstdlib>
#include <raylib.h>
#include <memory>
#include "player.hpp"
#include "button.hpp"
#include "game.hpp"

Game::Game() : buttonTexture(LoadTexture("assets/button.png")), 
  startButton(std::make_unique<Button>(200, 200, 20, "start", buttonTexture, [this]() 
        {
        gs = PlayState;
        player = std::make_unique<Player>();
        })), 
  closeButton(std::make_unique<Button>(200, 230, 20, "close", buttonTexture, [this]()
        {
        quit = true;
        })), 
  exitButton(std::make_unique<Button>(200, 230, 20, "exit", buttonTexture, [this]()
        {
        pauseGame = false;
        gs = MenuState;
        player->writebinary();
        player.reset();
        })),
  resumeButton(std::make_unique<Button>(200, 200, 20, "resume", buttonTexture, [this]()
        {
        pauseGame = false;        
        })) {}
// player(std::make_unique<Player>(x, y)), 
Game::~Game() {
  UnloadTexture(buttonTexture);
}

void Game::Update() {
  switch (gs) {
    case PlayState:
      if (IsKeyDown(KEY_ESCAPE)) {
        pauseGame = true;
      }
      if (!pauseGame) {
        player->Update();
      } else {
        if (resumeButton->isClicked()) {
          resumeButton->Action();
        }
        if (exitButton->isClicked()) {
          exitButton->Action();
        }
      }
      break;
    case MenuState:
      if (startButton->isClicked()) {
        startButton->Action();
      }
      if (exitButton->isClicked()) {
        closeButton->Action();
      }
      break;
    /*case CreateWorldState:
      std::cout << "sekarang berada di state create new world" << std::endl;
      break;
    case WorldState:
      std::cout << "sekarang berada di state world list" << std::endl;
      break;
      */
  }
}

void Game::Drawing() {
  BeginDrawing();
  ClearBackground(WHITE);
  switch (gs) {
    case PlayState:
      player->Drawing();

      if (pauseGame) {
        resumeButton->Draw();
        exitButton->Draw();
      }
      break;
    case MenuState:
      startButton->Draw();
      closeButton->Draw();
      break;
    /*case CreateWorldState:
      std::cout << "sekarang berada di update state create new world" << std::endl;
      break;
    case WorldState:
      std::cout << "sekarang berada di update state world list" << std::endl;
      break;
      */
  }
  EndDrawing();
}

void Game::Run() {
  while (!quit && !WindowShouldClose()) {
    Update();
    Drawing();
  }
}
