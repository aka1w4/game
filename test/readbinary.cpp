#include <fstream>
#include <vector>
#include <iostream>

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
  std::ifstream in("map.bin");
  if (!in) {
    std::cout << "error" << std::endl;
  }

  Map m;
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

    m.Tilemaps.push_back(tm);
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

    m.layers.push_back(layer);
  }

  for (const auto tm : m.Tilemaps) {
    std::cout << "pathimage: " << tm.pathimage << std::endl;
  }
  return 0;
}
