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
  int x, y, map;
  std::vector<Layer> layers;
  std::vector<Tilemap> Tilemaps;
};

int main() {
  std::ifstream in("map.bin");
  if (!in) {
    std::cout << "error" << std::endl;
  }

  std::vector<std::string> images;

  int lenImages;
  in.read((char*)&lenImages, sizeof(int));
  images.resize(lenImages);
  for (int i=0; i < lenImages; i++) {
    int len;
    in.read(reinterpret_cast<char*>(&len), sizeof(int));
    images[i].resize(len);
    in.read(&images[i][0], len);
  }

  std::vector<Map> maps;
  int mapCount;
  in.read((char*)&mapCount, sizeof(int));

  for(int i=0; i < mapCount; i++) {
    Map m;

    in.read((char*)&m.map, sizeof(int));
    in.read((char*)&m.x, sizeof(int));
    in.read((char*)&m.y, sizeof(int));

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

    maps.push_back(m);
  }

  for (const auto &m : maps) {
    std::cout << "map ke: " << m.map << std::endl;
  }

  for (const auto &image : images) {
    std::cout << "path: " << image << std::endl;
  }
  
  return 0;
}
