#include "camera.hpp"
#include "../../include/raylib/raylib.h"

float CameraGame::clamp(float playerpos, float min, float max) {
  if (playerpos < min) return min;
  if (playerpos > max) return max;

  return playerpos;
}

void CameraGame::Update(Vector2 playerpos) {
  float ViewW = (GetScreenWidth() * 0.5f)  / cam.zoom;
  float ViewH = (GetScreenHeight() * 0.5f) / cam.zoom;

  float minCamX = ViewW;
  float maxCamX = mapMax - ViewW;
  float minCamY = ViewH;
  float maxCamY = mapMax - ViewH;

  if (mapMax <= GetScreenWidth() / cam.zoom) {
    cam.target.x = mapMax * 0.5f;
  } else {
    cam.target.x = clamp(playerpos.x, minCamX, maxCamX);
  }

  if (mapMax <= GetScreenHeight() / cam.zoom) {
    cam.target.y = mapMax * 0.5f;
  } else {
    cam.target.y = clamp(playerpos.y, minCamY, maxCamY);
  }
}
