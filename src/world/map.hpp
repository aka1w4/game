#ifndef LAYER
#define LAYER

#include <vector>
#include <string>
#include <raylib.h>

struct Layer {
  int width, height, id;
  std::string name;
  std::vector<int> datas;
};

struct Tilemap {
  int firstgid, columns, tilecount, tilewidth, tileheight;
  std::string pathimage;
  Texture2D image;
};

struct Collisions {
  Rectangle src, box;
  Vector2 pos;
  const Texture2D* img;
};

class Map {
  private:
    std::vector<Layer> ls;
    std::vector<Tilemap> tms;

  public:
    std::vector<Collisions> collisions;
    Map(const std::string& pathmap);
    ~Map();
    void DrawBackground();
    void DrawForeground();
    void LoadResources();
};

#endif // !LAYER
