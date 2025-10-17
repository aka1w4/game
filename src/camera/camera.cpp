#include "camera.hpp"
#include "../../include/raylib/raylib.h"
#include <algorithm>

void CameraGame::Update(Vector2 playerpos) {
  float halfViewW = cam.offset.x / cam.zoom;
  float halfViewH = cam.offset.y / cam.zoom;

  float minCamX = halfViewW;
  float maxCamX = mapMax - halfViewW;
  float minCamY = halfViewH;
  float maxCamY = mapMax - halfViewH;

  if (mapMax <= GetScreenWidth() / cam.zoom) {
    cam.target.x = mapMax / 2.0f;
  } else {
    cam.target.x = std::clamp(playerpos.x, minCamX, maxCamX);
  }

  if (mapMax <= GetScreenHeight() / cam.zoom) {
    cam.target.y = mapMax / 2.0f;
  } else {
    cam.target.y = std::clamp(playerpos.y, minCamY, maxCamY);
  }
}
