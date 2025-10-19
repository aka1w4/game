#include "camera.hpp"
#include "../../include/raylib/raylib.h"
#include <algorithm>

void CameraGame::Update(Vector2& playerpos, Vector2& sizeMap) {
  float halfViewW = cam.offset.x / cam.zoom;
  float halfViewH = cam.offset.y / cam.zoom;
  
  float MapX = sizeMap.x * 16.0f;
  float MapY = sizeMap.y * 16.0f;

  float minCamX = halfViewW;
  float maxCamX = MapX - halfViewW;
  float minCamY = halfViewH;
  float maxCamY = MapY - halfViewH;

  if (MapX <= GetScreenWidth() / cam.zoom) {
    cam.target.x = MapX / 2.0f;
  } else {
    cam.target.x = std::clamp(playerpos.x, minCamX, maxCamX);
  }

  if (MapY <= GetScreenHeight() / cam.zoom) {
    cam.target.y = MapY / 2.0f;
  } else {
    cam.target.y = std::clamp(playerpos.y, minCamY, maxCamY);
  }
}
