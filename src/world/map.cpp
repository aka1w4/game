#include <fstream>
#include "../../include/raylib/raylib.h"
#include <string>
#include "map.hpp"

Map::Map(const std::string& pathmap) {
  std::ifstream in(pathmap);
  if (!in) {
    throw std::runtime_error("gagal membaca");
  } 

  int mapCount;
  in.read((char*)&mapCount, sizeof(int));

  for(int i=0; i < mapCount; i++) {
    StructMap m;

    in.read((char*)&m.map, sizeof(int));
    in.read((char*)&m.x, sizeof(int));
    in.read((char*)&m.y, sizeof(int));

    sizeMap.x += m.x;
    sizeMap.y += m.y;

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

      m.tms.push_back(tm);
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

      m.ls.push_back(layer);
    }

    maps.push_back(m);
  }
}

void Map::LoadResources() {
  for (auto &m : maps) {
    for (auto &tm : m.tms) {
      tm.image = LoadTexture(tm.pathimage.c_str());
      if (tm.image.id == 0) {
        throw std::runtime_error("gagal load image");
      }
    }

    for (const auto &l : m.ls) {
      if (l.name != "collisions") { continue; }
      for (int y = 0; y < l.height; y++) {
        for (int x = 0; x < l.width; x++) {
          int idx = y * l.width + x;
          if (idx >= l.datas.size()) { continue; }
          int tileId = l.datas[idx];
          if (tileId == 0) continue;
          for (auto &tm : m.tms) {
            if (tileId >= tm.firstgid && tileId < tm.firstgid + tm.tilecount) {
              int tileX = (tileId - tm.firstgid) % tm.columns;
              int tileY = (tileId - tm.firstgid) / tm.columns;

              Collisions c;
              c.src.x = tileX * tm.tilewidth;
              c.src.y = tileY * tm.tileheight;
              c.src.width = tm.tilewidth;
              c.src.height = tm.tileheight;

              c.pos.x = float(x + m.x) * tm.tilewidth;
              c.pos.y = float(y + m.y) * tm.tileheight;

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
}

Map::~Map() {
  for (auto &m : maps) {
    for (auto &tm : m.tms) {
      UnloadTexture(tm.image);
    }
  }
}

void Map::DrawBackground() {
  for (const auto &m : maps) {
    if (m.map != location) { continue; }
    for (const auto &l : m.ls) {
      if (l.name != "background") { continue; }
      for (int y = 0; y < l.height; y++) {
        for (int x = 0; x < l.width; x++) {
          int idx = y * l.width + x;
          if (idx >= l.datas.size()) { continue; }
          int tileId = l.datas[idx];
          if (tileId == 0) continue;

          for (const auto &tm : m.tms) {
            if (tileId >= tm.firstgid && tileId < tm.firstgid + tm.tilecount) {
            int tileX = (tileId - tm.firstgid) % tm.columns;
            int tileY = (tileId - tm.firstgid) / tm.columns;

            Rectangle src = Rectangle{(float)tileX * tm.tilewidth, (float)tileY * tm.tileheight, (float)tm.tilewidth, (float)tm.tileheight};
            Vector2 pos = Vector2{(float)(x + m.x) * tm.tilewidth, (float)(y + m.y) * tm.tileheight};
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
  for (const auto &c : collisions) {
      DrawTextureRec(*c.img, c.src, c.pos, WHITE);
  }
}

void Map::DrawForeground() {
  for (const auto &m : maps) {
    if (m.map != location) { continue; }
    for (const auto &l : m.ls) {
      if (l.name != "foreground") { continue; }
      for (int y = 0; y < l.height; y++) {
        for (int x = 0; x < l.width; x++) {
          int idx = y * l.width + x;
          if (idx >= l.datas.size()) { continue; }
          int tileId = l.datas[idx];
          if (tileId == 0) continue;

          for (const auto &tm : m.tms) {
            if (tileId >= tm.firstgid && tileId < tm.firstgid + tm.tilecount) {
              int tileX = (tileId - tm.firstgid) % tm.columns;
              int tileY = (tileId - tm.firstgid) / tm.columns;

              Rectangle src = Rectangle{(float)tileX * tm.tilewidth, (float)tileY * tm.tileheight, (float)tm.tilewidth, (float)tm.tileheight};
              Vector2 pos = Vector2{(float)(x + m.x) * tm.tilewidth, (float)(y + m.y) * tm.tileheight};
              DrawTextureRec(
                  tm.image, 
                  src,
                  pos, 
                  WHITE
              );
            } 
          }
        }
      }
    }
  }
}

void Map::Update(Vector2& playerpos) {
  if (playerpos.x > 100 * 16) {
    if (playerpos.y > 100 * 16) {
      sizeMap = Vector2{100, 100};
      location = 3;
    } else {
      sizeMap = Vector2{100, 0};
      location = 1;
    }
  } else {
    if (playerpos.y > 100 * 16) {
      sizeMap = Vector2{0, 100};
      location = 2;
    } else {
      sizeMap = Vector2{0, 0};
      location = 0;
    }
  }
}

std::vector<Collisions>& Map::GetCollisions() {
  return collisions;
}

Vector2& Map::GetSizeMap() {
  return sizeMap;
}
