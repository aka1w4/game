#include <fstream>
#include <raylib.h>
#include <string>
#include "map.hpp"
#include "../../inlcude/json.hpp"

Map::Map(const std::string& pathmap) {
  std::ifstream file(pathmap);
  if (!file) {
    throw std::runtime_error("gagal membaca");
  }

  nlohmann::json j;
  file >> j;

  /*l.datas = j["layers"].get<std::vector<Layer>>["data"].get<std::vector<int>>();
  l.id = j["layers"][0]["id"];
  l.width = j["layers"][0]["width"];
  l.height = j["layers"][0]["height"]; */
  for (auto& jl : j["layers"]) {
    Layer l;
    l.id = jl["id"];
    l.name = jl["name"];
    l.width = jl["width"];
    l.height = jl["height"];
    l.datas = jl["data"].get<std::vector<int>>();
    ls.push_back(l);
  }

  /*tm.columns = j["tilesets"][0]["columns"];
  tm.firstgid = j["tilesets"][0]["firstgid"];
  tm.pathimage = j["tilesets"][0]["image"];
  tm.tilecount = j["tilesets"][0]["tilecount"];
  tm.tilewidth = j["tilesets"][0]["tilewidth"];
  tm.tileheight = j["tilesets"][0]["tileheight"]; */

  for (auto& jtm : j["tilesets"]) {
    Tilemap tm;
    tm.columns = jtm["columns"];
    tm.firstgid = jtm["firstgid"];
    tm.pathimage = jtm["image"];
    tm.tilecount = jtm["tilecount"];
    tm.tilewidth = jtm["tilewidth"];
    tm.tileheight = jtm["tileheight"];
    tms.push_back(tm);
  }

  for (auto &tm : tms) {
    while (tm.pathimage.rfind("../", 0) == 0) {
      tm.pathimage.erase(0, 3);
    }
    tm.pathimage = std::string("assets/") + tm.pathimage;
  }
}

void Map::LoadResources() {
  for (auto &tm : tms) {
    tm.image = LoadTexture(tm.pathimage.c_str());
    if (tm.image.id == 0) {
      throw std::runtime_error("gagal load image");
    }
  }

  for (const auto &l : ls) {
    if (l.name != "foreground") { continue; }
    for (int y = 0; y < l.height; y++) {
      for (int x = 0; x < l.width; x++) {
        int idx = y * l.width + x;
        if (idx >= l.datas.size()) { continue; }
        int tileId = l.datas[idx];
        if (tileId == 0) continue;
        int tileX = (tileId - tms[0].firstgid) % tms[0].columns;
        int tileY = (tileId - tms[0].firstgid) / tms[0].columns;

        Collisions c;
        c.src.x = tileX * tms[0].tilewidth;
        c.src.y = tileY * tms[0].tileheight;
        c.src.width = tms[0].tilewidth;
        c.src.height = tms[0].tileheight;

        c.pos.x = x * tms[0].tilewidth;
        c.pos.y = y * tms[0].tileheight;

        c.box.x = c.pos.x;
        c.box.y = c.pos.y;
        c.box.width = c.src.width;
        c.box.height = c.src.height;

        collisions.push_back(c);
      }
    }
   }
}

Map::~Map() {
  for (auto &tm : tms) {
    UnloadTexture(tm.image);
  }
}

void Map::Draw() {
  for (const auto &l : ls) {
    if (l.name != "background") { continue; }
    for (int y = 0; y < l.height; y++) {
      for (int x = 0; x < l.width; x++) {
        int idx = y * l.width + x;
        if (idx >= l.datas.size()) { continue; }
        int tileId = l.datas[idx];
        if (tileId == 0) continue;

        for (const auto &tm : tms) {
          if (tileId >= tm.firstgid && tileId < tm.firstgid + tm.tilecount) {
            int tileX = (tileId - tm.firstgid) % tm.columns;
            int tileY = (tileId - tm.firstgid) / tm.columns;

            Rectangle src = Rectangle{(float)tileX * tm.tilewidth, (float)tileY * tm.tileheight, (float)tm.tilewidth, (float)tm.tileheight};
            Vector2 pos = Vector2{(float)x * tm.tilewidth, (float)y * tm.tileheight};
            DrawTextureRec(
                tm.image, 
                src,
                pos, 
                WHITE);
          } 
        }
      }
    }
  }
  for (const auto &c : collisions) {
    for (const auto &tm : tms) {
      DrawTextureRec(tm.image, c.src, c.pos, WHITE);
    }
  }
}
