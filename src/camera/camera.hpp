#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "../../include/raylib/raylib.h"

class CameraGame {
public:
  Camera2D cam;
  CameraGame(Camera2D cam) : cam(cam) {}
  void Update(Vector2 &playerpos, Vector2 &sizeMap);
};

#endif // !CAMERA_CPP
