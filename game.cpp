#include <raylib.h>
#include <memory>
#include "player.hpp"
#include "button.hpp"
#include "game.hpp"

Game::Game(float x, float y) : buttonTexture(LoadTexture("assets/button.png")) {
  player = std::make_unique<Player>(x, y);
  buttons.push_back(std::make_unique<StartButton>(200, 200, 20, "start", buttonTexture));
  buttons.push_back(std::make_unique<ExitButton>(200, 230, 20, "exit", buttonTexture));
}
Game::~Game() {
  UnloadTexture(buttonTexture);
}

void Game::Update() {
  player->Update();
}

void Game::Drawing() {
  BeginDrawing();
  ClearBackground(WHITE);
  for (auto &b : buttons) {
    b->Draw();
  }
  player->Drawing();
  for (auto &b : buttons) {
    if (b->isClicked()) {
      b->Action();
    }
  }
  EndDrawing();
}

void Game::Run() {
  while (!WindowShouldClose()) {
    Update();
    Drawing();
  }
}
