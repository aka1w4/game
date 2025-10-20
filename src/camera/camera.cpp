#include "camera.hpp"
#include "../../include/raylib/raylib.h"
#include <algorithm>

void CameraGame::Update(Vector2& playerpos, Vector2& sizeMap) {
  float halfViewW = cam.offset.x / cam.zoom;
  float halfViewH = cam.offset.y / cam.zoom;

  // menghitung nilai awal width dan height
  constexpr float MAP_WIDTH = 100 * 16;
  constexpr float MAP_HEIGHT = 100 * 16;

  // menghitung worldStart dari sizeMap
  float worldStartX = sizeMap.x * 16.0f;
  float worldStartY = sizeMap.y * 16.0f;

  // menghitung worldEnd 
  float worldEndX = worldStartX + MAP_WIDTH;
  float worldEndY = worldStartY + MAP_HEIGHT;

  // menentukan minimal offset camera
  float minCamX = worldStartX + halfViewW;
  float minCamY = worldStartY + halfViewH;
 
  // menentukan maksimal offset camera 
  float maxCamX = worldEndX - halfViewW;
  float maxCamY = worldEndY - halfViewH;

  if (worldEndX <= GetScreenWidth() / cam.zoom) {
    cam.target.x = worldEndX / 2.0f;
  } else {
    cam.target.x = std::clamp(playerpos.x, minCamX, maxCamX);
  }

  if (worldEndY <= GetScreenHeight() / cam.zoom) {
    cam.target.y = worldEndY / 2.0f;
  } else {
    cam.target.y = std::clamp(playerpos.y, minCamY, maxCamY);
  }
}
