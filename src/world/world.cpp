#include "world.hpp"
#include "map.hpp"
#include "../ui/button.hpp"
#include "../ui/textinput.hpp"
#include "../db/db.hpp"
#include "../player/player.hpp"
#include <functional>
#include <memory>
#include <raylib.h>
#include <filesystem>
#include <chrono>
#include <thread>

NewWorld::NewWorld(Texture2D& inputT, Texture2D& buttonT, std::function<void(SavePlayer&, const std::string&)> play) : 
  play(play),
  textinput_name(std::make_unique<Textinput>(240, 60, 183, 29, 40, inputT)), 
  submit(std::make_unique<Button>(240,120, 183, 29, 40, "submit", buttonT, [this]()
        {
        SavePlayer sp = SavePlayer{Vector2{100, 100}, Down, false};
        createNewWorld(textinput_name->GetText(), 1, sp);

        if (this->play) this->play(sp, textinput_name->GetText());
        })) 
  {
    if(!std::filesystem::exists("world")) {
      std::filesystem::create_directories("world");
    }
  }

void NewWorld::Update() {
  textinput_name->checkPos();

  if (textinput_name->inTextInput()) {
    textinput_name->EditInputText();
  }

  if (textinput_name->GetText().size() >= 5) {
    if (submit->isClicked()) {
      submit->Action();
      textinput_name->ClearText();
    }
  }
 }

void NewWorld::Draw() {
  textinput_name->Draw();
  submit->Draw();
}

void NewWorld::ClearText() {
  textinput_name->ClearText();
}

World::World(SavePlayer& sp, const std::string& path) : 
  path(path)
{
  std::thread loadmap([this]() {
       m = std::make_unique<Map>("assets/map/map.json");
  });

  std::thread loadplayer([this](SavePlayer& sp) {
      player = std::make_unique<Player>(sp.pos, sp.f, sp.facingright);
      cam = Camera2D{Vector2{GetScreenWidth()/2.0f, GetScreenHeight()/2.0f}, sp.pos, 0.0f, 1.0f};
  }, std::ref(sp));

  loadplayer.join();
  loadmap.join();
  lastSave = std::chrono::steady_clock::now();
  m->LoadResources();
  player->LoadResourcesPlayer();
}

World::~World() {
  if (player) WriteWorld();
}

void World::Update(bool& pauseGame) {
  auto now = std::chrono::steady_clock::now();
  cam.target = player->GetPlayerpos();
  if (!pauseGame) player->Update();
  if (std::chrono::duration_cast<std::chrono::minutes>(now - lastSave).count() >= 5) {
    WriteWorld();
    lastSave = now;
  }
}

void World::Draw() {
  BeginMode2D(cam);
    //DrawRectangle(100, 100, 100, 100, BLACK);
    m->Draw();
    player->Draw();
  EndMode2D();
}

void World::WriteWorld() {
  SavePlayer sp = player->GetPlayer();
  writeBinaryPlayer(path, sp);
}
