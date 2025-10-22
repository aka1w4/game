#include "world.hpp"
#include "map.hpp"
#include "../ui/ui.hpp"
#include "../db/db.hpp"
#include "../player/player.hpp"
#include "../entity/entity.hpp"
#include "../camera/camera.hpp"
#include <functional>
#include <memory>
#include <filesystem>
#include <chrono>
#include <thread>
#include "../../include/stduuid/uuid.h"
#include "../../include/raylib/raylib.h"
#include "../../include/raylib/raymath.h"

NewWorld::NewWorld(Texture2D& inputT, Texture2D& buttonT, std::function<void(const std::string&)> p) : 
  play(p),
  textinput_name(std::make_unique<Textinput>(240, 60, 183, 29, 40, inputT)), 
  submit(std::make_unique<Button>(240,120, 183, 29, 40, "submit", buttonT, [this]()
        {
        uuids::uuid uuid = CreateUUID();
        SaveEntity sp{Vector2{100, 100}, Down, false, 10, 10, uuid}; // membuat data player baru
        createNewWorld(textinput_name->GetText(), 1, sp);                 // mebuat world baru

        if (this->play) this->play(textinput_name->GetText());        // menjalankan world
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

World::World(const std::string& path, Texture2D& buttonTexture) : 
  ls(path),
  camGame(Camera2D{}),
  healthTexture(LoadTexture("assets/health.png")),
  respwanButton(Button(0, 0, 183, 29, 40, "resume", buttonTexture,[this]() {
        player->RespwanPlayer(setPoint);
  }))
{
  SaveEntity sp = ls.readbinaryPlayer();
  setPoint = sp.pos;
  playerTextures[isIdle] = LoadTexture("assets/16x32idle.png");
  playerTextures[isWalk] = LoadTexture("assets/16x32walk.png");

  std::thread loadentity([this]() {
      std::vector<SaveEntity> entities = ls.readbinaryEntity();

      for (auto &e : entities) {
        enems.push_back(std::make_unique<Enemy>(e, playerTextures));
      }
  });

  // loadmap di thread
  std::thread loadmap([this]() {
       m = std::make_unique<Map>("assets/map/map.bin");
  });

  // loadplayer di thread
  std::thread loadplayer([this, sp]() {
      player = std::make_unique<Player>(sp, playerTextures, healthTexture);
      camGame = Camera2D{Vector2{GetScreenWidth()/2.0f, GetScreenHeight()/2.0f}, sp.pos, 0.0f, 2.0f};
  });

  loadplayer.join();
  loadmap.join();
  loadentity.join();
  lastSave = std::chrono::steady_clock::now();
  m->LoadResources();
}

World::~World() {
  if (player) WritePlayer();
  std::thread twriteentity([this](){
      WriteEntity();
  });

  for (auto &texture : playerTextures) {
    UnloadTexture(texture);
  }
  UnloadTexture(healthTexture);
  twriteentity.join();
}

void World::Update(bool& pauseGame) {
  // waktu sekarang
  auto now = std::chrono::steady_clock::now();

  std::thread tupdateeemy([this]() {
      for (const auto &e : enems) {
          e->Update();
      }
  });

  // test death player
  if (IsKeyPressed(KEY_F)) {
    player->Death();
  }
 
  if (!player->GetPlayerDeath()) {
    // oldpos dan newpos player
    Rectangle oldPos = player->GetRec();
    if (!pauseGame) player->Update();
    Rectangle newPos = player->GetRec();
    
    Rectangle recX = oldPos;
    recX.x = newPos.x;
    for (const auto &c : m->GetCollisions()) {
      // mengecek apakah posisi player x bertabrakan dengan c.box
      if (CheckCollisionRecs(recX, c.box)) {
        newPos.x = oldPos.x;
        break;
      }
    }

    Rectangle recY = oldPos;
    recY.y = newPos.y;
    for (const auto &c : m->GetCollisions()) {
      // mengecek apakah posisi player y bertabrakan dengan c.box
      if (CheckCollisionRecs(recY, c.box)) {
        newPos.y = oldPos.y;
        break;
      }
    }

    if (newPos.x > 3180 || newPos.x < 0) {
      newPos.x = oldPos.x;
    }

    if (newPos.y > 3170 || newPos.y < 0) {
      newPos.y = oldPos.y;  
    }

    Vector2 posPlayer{newPos.x, newPos.y};
    player->UpdatePos(posPlayer); // mengupdate posisi baru player
    m->Update(posPlayer);
    camGame.Update(posPlayer, m->GetSizeMap());  // mengikuti posisi player 
    
    // testing
    std::thread tfollowplayer([this, &posPlayer]() {
        for (const auto &e : enems) {
          if (Vector2Distance(posPlayer, e->GetPosEntity()) < 100.0f) {
            e->FollowPlayer(posPlayer);
          }
        }
    });

    tfollowplayer.join();
  } else {
    if (respwanButton.isClicked()) {
      respwanButton.Action();
    }
  }

  tupdateeemy.join();

  // mengecek apakah waktu sekarang sudah lebih dari 5 menit
  if (std::chrono::duration_cast<std::chrono::minutes>(now - lastSave).count() >= 5) {
    WritePlayer();
    std::thread twriteentity([this](){
        WriteEntity();
    });

    twriteentity.join();
    lastSave = now; // menyimpan waktu sekarang ke lastsave
  }
}

void World::Draw() {
  BeginMode2D(camGame.cam);
    m->DrawBackground();
    player->Draw();
    std::thread tdrawenemy([this]() {
        for (const auto &e : enems) {
          e->Draw();
        }
    });
    tdrawenemy.join();
    m->DrawForeground();
  EndMode2D();
  player->DrawHeart();
  if (player->GetPlayerDeath()) {
    DrawRectangleRec(Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, Fade(RED, 0.5f));
    respwanButton.Draw();
  }
}

void World::WritePlayer() {
  SaveEntity sp = player->GetPlayer();
  ls.writeBinaryPlayer(sp);
}

void World::WriteEntity() {
  for (const auto &e : enems) {
    SaveEntity se = e->GetEntity();
    ls.writeBinaryEntity(se);
  }
}
