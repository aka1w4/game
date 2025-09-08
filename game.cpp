#include <iostream>
#include <raylib.h>
#include <memory>
#include "player.hpp"
#include "button.hpp"
#include "game.hpp"

Game::Game() : buttonTexture(LoadTexture("assets/button.png")), player(std::make_unique<Player>(100, 100)),
  startButton(std::make_unique<Button>(200, 200, 20, "start", buttonTexture, [this]() {
        //player = std::make_unique<Player>(100, 100); // bikin player baru
        gs = PlayState;
        })), 
  exitButton(std::make_unique<Button>(200, 230, 20, "exit", buttonTexture, [this]() {
        quit = true;
        })) {}
// player(std::make_unique<Player>(x, y)), 
Game::~Game() {
  UnloadTexture(buttonTexture);
}

void Game::Update() {
  switch (gs) {
    case PlayState:
      if (player) {
        player->Update();
      } else {
        TraceLog(LOG_INFO, "error");
      }
      break;
    case MenuState:
      if (startButton->isClicked()) {
        startButton->Action();
      }
      if (exitButton->isClicked()) {
        exitButton->Action();
      }
      break;
    case CreateWorldState:
      std::cout << "sekarang berada di state create new world" << std::endl;
      break;
    case WorldState:
      std::cout << "sekarang berada di state world list" << std::endl;
      break;
  }
}

void Game::Drawing() {
  BeginDrawing();
  ClearBackground(WHITE);
  switch (gs) {
    case PlayState:
      if(player) {
        player->Drawing();
      }
      break;
    case MenuState:
      startButton->Draw();
      exitButton->Draw();
      break;
    case CreateWorldState:
      std::cout << "sekarang berada di update state create new world" << std::endl;
      break;
    case WorldState:
      std::cout << "sekarang berada di update state world list" << std::endl;
      break;
  }
  EndDrawing();
}

void Game::Run() {
  while (!quit && !WindowShouldClose()) {
    Update();
    Drawing();
  }
}
