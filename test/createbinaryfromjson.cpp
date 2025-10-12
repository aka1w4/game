#include <fstream>
#include <vector>
#include "../include/json.hpp"

struct Layer {
  int width, height, id;
  std::string name;
  std::vector<int> datas;
};

struct Tilemap {
  int firstgid, columns, tilecount, tilewidth, tileheight;
  std::string pathimage;
};

struct Map {
  std::vector<Layer> layers;
  std::vector<Tilemap> Tilemaps;
};

int main() {
  std::ifstream input("../assets/map/map.json");
  nlohmann::json j;

  input >> j;
  Map m;

  for (auto& jl : j["layers"]) {
    Layer l;
    l.id = jl["id"];
    l.name = jl["name"];
    l.width = jl["width"];
    l.height = jl["height"];
    l.datas = jl["data"].get<std::vector<int>>();
    m.layers.push_back(l);
  }

  for (auto& jtm : j["tilesets"]) {
    Tilemap tm;
    tm.columns = jtm["columns"];
    tm.firstgid = jtm["firstgid"];
    tm.pathimage = jtm["image"];
    tm.tilecount = jtm["tilecount"];
    tm.tilewidth = jtm["tilewidth"];
    tm.tileheight = jtm["tileheight"];
    m.Tilemaps.push_back(tm);
  }

  std::ofstream out("map.bin", std::ios::binary);

  int tilemapCount = m.Tilemaps.size();
  int layerCount = m.layers.size();

  out.write((char*)&tilemapCount, sizeof(int));
  for (auto &tm : m.Tilemaps) {
    out.write((char*)&tm.firstgid, sizeof(int));
    out.write((char*)&tm.columns, sizeof(int));
    out.write((char*)&tm.tilecount, sizeof(int));
    out.write((char*)&tm.tilewidth, sizeof(int));
    out.write((char*)&tm.tileheight, sizeof(int));
    while (tm.pathimage.rfind("../", 0) == 0) {
      tm.pathimage.erase(0, 3);
    }
    tm.pathimage = std::string("assets/") + tm.pathimage;
    int len = tm.pathimage.size();
    out.write((char*)&len, sizeof(int));
    out.write(tm.pathimage.data(), len);
  }

  out.write((char*)&layerCount, sizeof(int));
  for (auto &layer : m.layers) {
    out.write((char*)&layer.height, sizeof(int));
    out.write((char*)&layer.width, sizeof(int));
    out.write((char*)&layer.id, sizeof(int));
    int len = layer.name.size();
    out.write((char*)&len, sizeof(int));
    out.write(layer.name.data(), len);

    int dataCount = layer.datas.size();
    out.write((char*)&dataCount, sizeof(int));
    out.write(reinterpret_cast<const char*>(layer.datas.data()), dataCount * sizeof(int));
  }
  return 0;
}
