#ifndef WORLD
#define WORLD

#include "../ui/textinput.hpp"
#include "../ui/button.hpp"
#include "../player/player.hpp"
#include <memory>
#include <chrono>
#include <raylib.h>
#include <string>

class NewWorld {
  private:
    std::string name;
    std::unique_ptr<Textinput> textinput_name;
    std::unique_ptr<Button> submit;
    std::function<void(const SavePlayer&, const std::string&)> play;

  public:
    NewWorld(Texture2D& inputT, Texture2D& buttonT, std::function<void(const SavePlayer&, const std::string&)> play);
    void Draw();
    void Update();
    void ClearText();
};

class World {
  private:
    std::unique_ptr<Player> player;
    std::string path;
    std::chrono::time_point<std::chrono::steady_clock> lastSave;

  public:
    World(SavePlayer sp, const std::string& path);
    ~World();
    void Update(bool& pauseGame);
    void Draw();
    void WriteWorld();
};

#endif // !WORLD
