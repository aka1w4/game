#include <fstream>
#include <raylib.h>
#include <string>
#include "map.hpp"
//#include "../../include/json.hpp"

Map::Map(const std::string& pathmap) {
  std::ifstream in(pathmap);
  if (!in) {
    throw std::runtime_error("gagal membaca");
  } 
  int layerCount;
  int tilemapCount;
  in.read((char*)&tilemapCount, sizeof(int));

  for (int i = 0; i < tilemapCount; i++) {
    Tilemap tm;
    in.read((char*)&tm.firstgid, sizeof(int));
    in.read((char*)&tm.columns, sizeof(int));
    in.read((char*)&tm.tilecount, sizeof(int));
    in.read((char*)&tm.tilewidth, sizeof(int));
    in.read((char*)&tm.tileheight, sizeof(int));

    int len;
    in.read((char*)&len, sizeof(int));
    tm.pathimage.resize(len);
    in.read(&tm.pathimage[0], len);

    tms.push_back(tm);
  }

  in.read((char*)&layerCount, sizeof(int));
  for (int i = 0; i < layerCount; i++) {
    Layer layer;
    in.read((char*)&layer.height, sizeof(int));
    in.read((char*)&layer.width, sizeof(int));
    in.read((char*)&layer.id, sizeof(int));

    int len;
    in.read((char*)&len, sizeof(int));
    layer.name.resize(len);
    in.read(&layer.name[0], len);

    int dataCount;
    in.read((char*)&dataCount, sizeof(int));
    layer.datas.resize(dataCount);
    in.read(reinterpret_cast<char*>(layer.datas.data()), dataCount * sizeof(int));

    ls.push_back(layer);
  }

  /*nlohmann::json j;
  file >> j;

  for (auto& jl : j["layers"]) {
    Layer l;
    l.id = jl["id"];
    l.name = jl["name"];
    l.width = jl["width"];
    l.height = jl["height"];
    l.datas = jl["data"].get<std::vector<int>>();
    ls.push_back(l);
  }

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
  }*/
}

void Map::LoadResources() {
  for (auto &tm : tms) {
    tm.image = LoadTexture(tm.pathimage.c_str());
    if (tm.image.id == 0) {
      throw std::runtime_error("gagal load image");
    }
  }

  for (const auto &l : ls) {
    if (l.name != "collisions") { continue; }
    for (int y = 0; y < l.height; y++) {
      for (int x = 0; x < l.width; x++) {
        int idx = y * l.width + x;
        if (idx >= l.datas.size()) { continue; }
        int tileId = l.datas[idx];
        if (tileId == 0) continue;
        for (auto &tm : tms) {
          if (tileId >= tm.firstgid && tileId < tm.firstgid + tm.tilecount) {
            int tileX = (tileId - tm.firstgid) % tm.columns;
            int tileY = (tileId - tm.firstgid) / tm.columns;

            Collisions c;
            c.src.x = tileX * tm.tilewidth;
            c.src.y = tileY * tm.tileheight;
            c.src.width = tm.tilewidth;
            c.src.height = tm.tileheight;

            c.pos.x = x * tm.tilewidth;
            c.pos.y = y * tm.tileheight;

            c.box.x = c.pos.x;
            c.box.y = c.pos.y;
            c.box.width = c.src.width;
            c.box.height = c.src.height;

            c.img = &tm.image;
            collisions.push_back(c);
            break;
          }
        }
      }
    }
   }
}

Map::~Map() {
  for (auto &tm : tms) {
    UnloadTexture(tm.image);
  }
}

void Map::DrawBackground() {
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
      DrawTextureRec(*c.img, c.src, c.pos, WHITE);
  }
}

void Map::DrawForeground() {
  for (const auto &l : ls) {
    if (l.name != "foreground") { continue; }
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
}
