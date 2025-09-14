#include <chrono>
#include <iostream>
#include <raylib.h>
#include <memory>
#include "player/player.hpp"
#include "ui/button.hpp"
#include "game.hpp"

Game::Game() : buttonTexture(LoadTexture("assets/buttontest.png")),
  startButton(std::make_unique<Button>(200, 200, 183, 29, 20, "start", buttonTexture, [this]() 
        {
        gs = WorldListState;
        //player = std::make_unique<Player>();
        })), 
  closeButton(std::make_unique<Button>(200, 230, 183, 29, 20, "close", buttonTexture, [this]()
        {
        quit = true;
        })), 
  exitButton(std::make_unique<Button>(200, 230, 20, 183, 29, "exit", buttonTexture, [this]()
        {
        //lastSave = std::chrono::time_point<std::chrono::steady_clock>{};
        if (player) {
        player->writebinary();
        player.reset();
        }
        gs = MenuState;
        pauseGame = false;
        })),
  resumeButton(std::make_unique<Button>(200, 200, 183, 29, 20, "resume", buttonTexture, [this]()
        {
        //lastSave = std::chrono::steady_clock::now();
        pauseGame = false;        
        })),
  BackButton(std::make_unique<Button>(200, 230, 183, 29, 20, "back", buttonTexture, [this]()
        {
        if (gs == WorldListState) {
        gs = MenuState;
        } else if (gs == CreateWorldState) {
        gs = CreateWorldState;
        }
        })), 
  NewWorldButton(std::make_unique<Button>(200, 200, 183, 29, 20, "new world", buttonTexture, [this]()
        {
        gs = CreateWorldState;
        })), 
  CreateWorldButton(std::make_unique<Button>(200, 200, 183, 29, 20, "create", buttonTexture, [this]()
        {
        gs = PlayState;
        player = std::make_unique<Player>();
        })){}
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
    case WorldListState:
      if (NewWorldButton->isClicked()) {
        NewWorldButton->Action();
      }

      if (BackButton->isClicked()) {
        BackButton->Action();
      }
      break;
    case CreateWorldState:
      if (CreateWorldButton->isClicked()) {
        CreateWorldButton->Action();
      }

      if (BackButton->isClicked()) {
        BackButton->Action();
      }
      break;
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
    case WorldListState:
      NewWorldButton->Draw();
      BackButton->Draw();
      break;
    case CreateWorldState:
      CreateWorldButton->Draw();
      BackButton->Draw();
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
