#ifndef LAYER
#define LAYER

#include <vector>
#include <string>
#include "../../include/raylib/raylib.h"

struct Layer {
  int width, height, id;
  std::string name;
  std::vector<int> datas;
};

struct Tilemap {
  int firstgid, columns, tilecount, tilewidth, tileheight;
  std::string pathimage;
  Texture2D* image;
};

struct Collisions {
  Rectangle src, box;
  Vector2 pos;
  const Texture2D* img;
};

struct StructMap {
  int x, y, map;
  std::vector<Layer> ls;
  std::vector<Tilemap> tms;
};

struct ResourceMap {
  std::string pathimage;
  Texture2D texture;
};

class Map {
  private:
    std::vector<StructMap> maps;
    std::vector<ResourceMap> resourceMap;
    Vector2 sizeMap{0,0};
    std::vector<Collisions> collisions;
    int location = 0;

  public:
    Map(const std::string& pathmap);
    ~Map();
    std::vector<Collisions>& GetCollisions();
    Vector2& GetSizeMap();
    void DrawBackground();
    void DrawForeground();
    void LoadResources();
    void Update(Vector2& playerpos);
};

#endif // !LAYER
