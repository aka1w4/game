#include <chrono>
#include <iostream>
#include <raylib.h>
#include <memory>
#include "player/player.hpp"
#include "ui/button.hpp"
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
        //lastSave = std::chrono::time_point<std::chrono::steady_clock>{};
        if (player) {
        player->writebinary();
        player.reset();
        }
        gs = MenuState;
        pauseGame = false;
        })),
  resumeButton(std::make_unique<Button>(200, 200, 20, "resume", buttonTexture, [this]()
        {
        //lastSave = std::chrono::steady_clock::now();
        pauseGame = false;        
        })) {}
// player(std::make_unique<Player>(x, y)), 
Game::~Game() {
  UnloadTexture(buttonTexture);
}

void Game::Update() {
  auto now = std::chrono::steady_clock::now();
  switch (gs) {
    case PlayState:
      if (IsKeyDown(KEY_ESCAPE)) {
        pauseGame = true;
        //lastSave = std::chrono::time_point<std::chrono::steady_clock>{};
      }
      if (!pauseGame) {
        if (player) player->Update();
      } else {
        if (resumeButton->isClicked()) {
          resumeButton->Action();
        }
        if (exitButton->isClicked()) {
          exitButton->Action();
        }
      }
      if (std::chrono::duration_cast<std::chrono::minutes>(now - lastSave).count() >= 5) {
        std::cout << "save data ke " << std::endl;
        if (player) player->writebinary();
        lastSave = now;
      }
      break;
    case MenuState:
      if (startButton->isClicked()) {
        startButton->Action();
      }
      if (closeButton->isClicked()) {
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
      if (player) player->Drawing();
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
