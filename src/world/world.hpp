#ifndef WORLD
#define WORLD

#include "../ui/textinput.hpp"
#include "../ui/button.hpp"
#include "../player/player.hpp"
#include "map.hpp"
#include <memory>
#include <chrono>
#include <raylib.h>
#include <string>

class NewWorld {
  private:
    std::string name;
    std::unique_ptr<Textinput> textinput_name;
    std::unique_ptr<Button> submit;
    std::function<void(SavePlayer&, const std::string&)> play;

  public:
    NewWorld(Texture2D& inputT, Texture2D& buttonT, std::function<void(SavePlayer&, const std::string&)> p);
    void Draw();
    void Update();
    void ClearText();
};

class World {
  private:
    std::unique_ptr<Player> player;
    Camera2D cam;
    std::unique_ptr<Map> m;
    std::chrono::time_point<std::chrono::steady_clock> lastSave;
    WriteBinary wb;

  public:
    World(SavePlayer& sp, const std::string& path, std::array<Texture2D, 2>& imgs);
    ~World();
    void Update(bool& pauseGame);
    void Draw();
    void WriteWorld();
};

#endif // !WORLD
