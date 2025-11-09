#include "../include/json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Layer {
  int width, height, id;
  std::string name;
  std::vector<int> datas;
};

struct Tilemap {
  int firstgid, columns, tilecount, tilewidth, tileheight;
  std::string pathimage;
};

struct StructMap {
  int x, y, map;
  std::vector<Layer> layers;
  std::vector<Tilemap> Tilemaps;
};

StructMap LoadMap(std::string &path, int i) {
  std::ifstream input(path);
  nlohmann::json j;

  input >> j;
  StructMap m;

  std::cout << i << std::endl;
  m.map = i;
  m.x = j["layers"][0]["x"];
  m.y = j["layers"][0]["y"];

  for (auto &jl : j["layers"]) {
    Layer l;
    l.id = jl["id"];
    l.name = jl["name"];
    l.width = jl["width"];
    l.height = jl["height"];
    l.datas = jl["data"].get<std::vector<int>>();
    m.layers.push_back(l);
  }

  for (auto &jtm : j["tilesets"]) {
    Tilemap tm;
    tm.columns = jtm["columns"];
    tm.firstgid = jtm["firstgid"];
    tm.pathimage = jtm["image"];
    tm.tilecount = jtm["tilecount"];
    tm.tilewidth = jtm["tilewidth"];
    tm.tileheight = jtm["tileheight"];
    m.Tilemaps.push_back(tm);
  }

  return m;
}

int main() {
  std::vector<std::string> maps = {
      "../assets/map/map.json",
      "../assets/map/map2.json",
      "../assets/map/map3.json",
      "../assets/map/map4.json",
  };

  std::vector<std::string> images = {"assets/tilemap_packed.png",
                                     "assets/TilesetField.png"};

  std::ofstream out("map.bin", std::ios::binary);

  int lenImages = images.size();
  out.write((char *)&lenImages, sizeof(int));

  for (const auto &image : images) {
    int len = image.size();
    out.write(reinterpret_cast<const char *>(&len), sizeof(int));
    out.write(image.data(), len);
  }

  // int dataCount = layer.datas.size();
  // out.write((char*)&dataCount, sizeof(int));
  // out.write(reinterpret_cast<const char*>(layer.datas.data()), dataCount *
  // sizeof(int));

  int mapCount = maps.size();
  out.write((char *)&mapCount, sizeof(int));

  for (int i = 0; i < mapCount; i++) {
    StructMap m = LoadMap(maps[i], i);

    out.write((char *)&m.map, sizeof(int));
    out.write((char *)&m.x, sizeof(int));
    out.write((char *)&m.y, sizeof(int));

    int tilemapCount = m.Tilemaps.size();
    int layerCount = m.layers.size();

    out.write((char *)&tilemapCount, sizeof(int));
    for (auto &tm : m.Tilemaps) {
      out.write((char *)&tm.firstgid, sizeof(int));
      out.write((char *)&tm.columns, sizeof(int));
      out.write((char *)&tm.tilecount, sizeof(int));
      out.write((char *)&tm.tilewidth, sizeof(int));
      out.write((char *)&tm.tileheight, sizeof(int));

      while (tm.pathimage.rfind("../", 0) == 0) {
        tm.pathimage.erase(0, 3);
      }
      tm.pathimage = std::string("assets/") + tm.pathimage;
      int len = tm.pathimage.size();
      out.write((char *)&len, sizeof(int));
      out.write(tm.pathimage.data(), len);
    }

    out.write((char *)&layerCount, sizeof(int));
    for (auto &layer : m.layers) {
      out.write((char *)&layer.height, sizeof(int));
      out.write((char *)&layer.width, sizeof(int));
      out.write((char *)&layer.id, sizeof(int));

      int len = layer.name.size();
      out.write((char *)&len, sizeof(int));
      out.write(layer.name.data(), len);

      int dataCount = layer.datas.size();
      out.write((char *)&dataCount, sizeof(int));
      out.write(reinterpret_cast<const char *>(layer.datas.data()),
                dataCount * sizeof(int));
    }
  }

  return 0;
}
