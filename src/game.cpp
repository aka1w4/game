#include <raylib.h>
#include <memory>
#include <string>
#include "db/db.hpp"
#include "player/player.hpp"
#include "ui/background.hpp"
#include "ui/button.hpp"
#include "world/world.hpp"
#include "game.hpp"

Game::Game() : 
  buttonTexture(LoadTexture("assets/button.png")),
  inputTextTexture(LoadTexture("assets/inputtext.png")),
  b1(800, 800, false, Down, isIdle, Vector2{0, 0}, true),
  b2(-10, -10, true, Left, isWalk, Vector2{50, 50}, true),
  b3(500, -10, true, Up, isWalk, Vector2{0, 0}, false),
  startButton(Button(0, 0, 183, 29, 40, "start", buttonTexture, [this]()
        {
        CreateButtonReadWorld();
        gs = WorldListState;
        })),
  closeButton(Button(0, 60, 183, 29, 40, "close", buttonTexture, [this]()
        {
        quit = true;
        })), 
  exitButton(Button(0, 60, 183, 29, 40, "exit",  buttonTexture, [this]()
        {
        if (world) {
        world->WriteWorld();
        world.reset();
        }
        CreateButtonReadWorld();
        gs = WorldListState;
        pauseGame = false;
        })),
  resumeButton(Button(0, 0, 183, 29, 40, "resume", buttonTexture,[this]()
        {
        pauseGame = false;        
        })),
  BackButton(Button(240, -240, 183, 29, 40, "back", buttonTexture,[this]()
        {
        if (gs == WorldListState) {
        gs = MenuState;
        } else if (gs == CreateWorldState) {
        newworld->ClearText();
        CreateButtonReadWorld();
        gs = WorldListState;
        }
        })),
  NewWorldButton(Button(-240, -240, 183, 29, 40, "new world", buttonTexture,[this]()
        {
        gs = CreateWorldState;
        })),
  newworld(std::make_unique<NewWorld>(inputTextTexture, buttonTexture, [this](SavePlayer& sp, const std::string& text)
        {
        world = std::make_unique<World>(sp, std::string(WORLD_NAME) + text);
        gs = PlayState;
        })) {}

Game::~Game() {
  UnloadTexture(buttonTexture);
  UnloadTexture(inputTextTexture);
}

void Game::Update() { 
  switch (gs) {
    case PlayState:
      {
        if (IsKeyDown(KEY_ESCAPE)) {
          pauseGame = true;
        }

        if(world) world->Update(pauseGame);

        if (pauseGame) {
          if (resumeButton.isClicked()) {
            resumeButton.Action();
          }
          if (exitButton.isClicked()) {
            exitButton.Action();
          }
        }
      }
      break;
    case MenuState:
      b1.Update();
      b2.Update();
      b3.Update();
      if (startButton.isClicked()) {
        startButton.Action();
      }

      if (closeButton.isClicked()) {
        closeButton.Action();
      }
      break;
    case WorldListState:
      for (auto &wb : wbs) {
        if (wb->isClicked()) {
          wb->Action();
        }
      }
      if (NewWorldButton.isClicked()) {
        NewWorldButton.Action();
      }

      if (BackButton.isClicked()) {
        BackButton.Action();
      }
      break;
    case CreateWorldState:

      newworld->Update();

      if (BackButton.isClicked()) {
        BackButton.Action();
      }
      break;
  }
}

void Game::Drawing() {
  BeginDrawing();
  ClearBackground(WHITE);
  switch (gs) {
    case PlayState:
      if (world) world->Draw();
      if (pauseGame) {
        resumeButton.Draw();
        exitButton.Draw();
      }
      break;
    case MenuState:
      b1.Draw();
      b2.Draw();
      b3.Draw();
      startButton.Draw();
      closeButton.Draw();
      break;
    case WorldListState:
      scrollofset -= (int)GetMouseWheelMove() * 10;
      if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        scrollofset -= 10;
      } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        scrollofset += 10;
      }
      for (auto &wb : wbs) {
        wb->Draw(scrollofset);
      }
      NewWorldButton.Draw();
      BackButton.Draw();
      break;
    case CreateWorldState:
      newworld->Draw();
      BackButton.Draw();
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

void Game::CreateButtonReadWorld() {
  wbs.clear();
  ws.readLevelWorld();
  int y = -120;
  for (const auto& d : ws.datas) {
    y += 60;
    wbs.push_back(std::make_unique<WorldButton>(0, y, 183, 29, 40, buttonTexture, d, [this](const WorldInfo& wi) {
          SavePlayer sp = readbinaryPlayer(wi.path);
          world = std::make_unique<World>(sp, wi.path);
          gs = PlayState;
    }));
  }
}
