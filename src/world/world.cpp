#include "world.hpp"
#include "map.hpp"
#include "../ui/button.hpp"
#include "../ui/textinput.hpp"
#include "../db/db.hpp"
#include "../player/player.hpp"
#include "../entity/entity.hpp"
#include <functional>
#include <memory>
#include <raylib.h>
#include <filesystem>
#include <chrono>
#include <thread>
#include <boost/uuid/uuid_generators.hpp>

NewWorld::NewWorld(Texture2D& inputT, Texture2D& buttonT, std::function<void(SaveEntity&, const std::string&)> p) : 
  play(p),
  textinput_name(std::make_unique<Textinput>(240, 60, 183, 29, 40, inputT)), 
  submit(std::make_unique<Button>(240,120, 183, 29, 40, "submit", buttonT, [this]()
        {
        boost::uuids::random_generator r;
        SaveEntity sp{Vector2{100, 100}, Down, false, 10, 10, r()}; // membuat data player baru
        createNewWorld(textinput_name->GetText(), 1, sp);                 // mebuat world baru

        if (this->play) this->play(sp, textinput_name->GetText());        // menjalankan world
        })) 
  {
    if(!std::filesystem::exists("world")) {
      std::filesystem::create_directories("world");
    }
  }

void NewWorld::Update() {
  textinput_name->checkPos(); // mengecek apakah di clic;
  // mengecek apakah textinput sudah di click
  if (textinput_name->inTextInput()) {
    textinput_name->EditInputText(); // edit text di textinput
  }

  // mengecek apakah text >= 5 
  if (textinput_name->GetText().size() >= 5) {
    // mengecek apakah button di click
    if (submit->isClicked()) {
      submit->Action();             // menjalankan Action
      textinput_name->ClearText();  // menghapus text
    }
  }
 }

void NewWorld::Draw() {
  // draw textinput dan submit
  textinput_name->Draw();
  submit->Draw();
}

void NewWorld::ClearText() {
  textinput_name->ClearText(); // menghapus text
}

World::World(SaveEntity& sp, const std::string& path, std::array<Texture2D, 2>& imgs, Texture2D& healthimg) : 
  wb(path),
  imgs(imgs)
{
  // loadmap di thread
  std::thread loadmap([this]() {
       m = std::make_unique<Map>("assets/map/map.json");
  });

  // loadplayer di thread
  std::thread loadplayer([this, sp, &imgs, &healthimg]() {
      player = std::make_unique<Player>(sp, imgs, healthimg);
      cam = Camera2D{Vector2{GetScreenWidth()/2.0f, GetScreenHeight()/2.0f}, sp.pos, 0.0f, 2.0f};
  });

  loadplayer.join();
  loadmap.join();
  lastSave = std::chrono::steady_clock::now();
  m->LoadResources();
}

World::~World() {
  if (player) WriteWorld();
}

void World::Update(bool& pauseGame) {
  // waktu sekarang
  auto now = std::chrono::steady_clock::now();

  for (const auto &e : enemys) {
      e->Update();
  }

  // oldpos dan newpos player
  Rectangle oldPos = player->GetRec();
  if (!pauseGame) player->Update();
  Rectangle newPos = player->GetRec();

  Rectangle recX = oldPos;
  recX.x = newPos.x;
  for (const auto &c : m->collisions) {
    // mengecek apakah posisi player x bertabrakan dengan c.box
    if (CheckCollisionRecs(recX, c.box)) {
      newPos.x = oldPos.x;
      break;
    }
  }

  Rectangle recY = oldPos;
  recY.y = newPos.y;
  for (const auto &c : m->collisions) {
    // mengecek apakah posisi player y bertabrakan dengan c.box
    if (CheckCollisionRecs(recY, c.box)) {
      newPos.y = oldPos.y;
      break;
    }
  }

  player->UpdatePos(Vector2{newPos.x, newPos.y}); // mengupdate posisi baru player
  cam.target = Vector2{newPos.x, newPos.y};       // mengikuti posisi player

  // mengecek apakah waktu sekarang sudah lebih dari 5 menit
  if (std::chrono::duration_cast<std::chrono::minutes>(now - lastSave).count() >= 5) {
    WriteWorld();
    lastSave = now; // menyimpan waktu sekarang ke lastsave
  }

  if (IsKeyPressed(KEY_E)) {
    boost::uuids::random_generator r;
    SaveEntity se{player->GetPlayerpos(), Down, false, 10, 10, r()};
    enemys.push_back(std::make_unique<Enemy>(se, imgs));
  }
}

void World::Draw() {
  BeginMode2D(cam);
    m->Draw();
    player->Draw();
    for (const auto &e : enemys) {
      e->Draw();
    }
  EndMode2D();
  player->DrawHeart();
}

void World::WriteWorld() {
  SaveEntity sp = player->GetPlayer();
  wb.writeBinaryPlayer(sp);
}
