#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "../../include/raylib/raylib.h"

// ukuran map dikali pixel tile
const float mapMax  = 100 * 16.0f;
//const float mapHeight = 100 * 16.0f;

class CameraGame {
  private:
    float clamp(float playerpos, float min, float max);
  public:
    Camera2D cam;
    CameraGame(Camera2D cam) : cam(cam) {}
    void Update(Vector2 playerpos);
};

#endif // !CAMERA_CPP
