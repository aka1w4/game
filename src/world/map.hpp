#ifndef LAYER
#define LAYER

#include <vector>
#include <string>
#include <raylib.h>

struct Layer {
  int width, height, id;
  std::vector<int> datas;
};

struct Tilemap {
  int firstgid, columns, tilecount, tilewidth, tileheight;
  std::string pathimage;
  Texture2D image;
};

class Map {
  private:
    std::vector<Layer> ls;
    std::vector<Tilemap> tms;

  public:
    Map(const std::string& pathmap);
    ~Map();
    void Draw();
    void LoadResources();
};

#endif // !LAYER
