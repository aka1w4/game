#ifndef WORLD
#define WORLD

#include "../ui/ui.hpp"
#include "../player/player.hpp"
#include "../entity/entity.hpp"
#include "map.hpp"
#include "../camera/camera.hpp"
#include <memory>
#include <chrono>
#include "../../include/raylib/raylib.h"
#include <string>
#include <vector>

/// @brief Representasi dunia baru
class NewWorld {
  private:
    std::unique_ptr<Textinput> textinput_name;                  // smart pointer textinput untuk mengelola instance text
    std::unique_ptr<Button> submit;                             // smart pointer button untuk membuat dunia baru
    std::function<void(const std::string&)> play;  // untuk menjalankan permainan

  public:
    /// @brief membuat dunia baru
    NewWorld(Texture2D& inputT, Texture2D& buttonT, std::function<void(const std::string&)> p);
    /// @brief draw textinput dan button
    void Draw();
    /// @brief update logika dunia baru
    void Update();
    /// @brief menghapus textinput
    void ClearText();
};

/// @brief Representasi dunia
class World {
  private:
    std::unique_ptr<Player> player;                               // smart pointer mengelola instance Player
    CameraGame camGame;                                           // kamera utama untuk mengatur posisi tampilan game
    std::unique_ptr<Map> m;                                       // smart pointer mengelola instance map
    std::chrono::time_point<std::chrono::steady_clock> lastSave;  // waktu terakhir menyimpan
    LoadAndSave ls;                                               // untuk menulis data binary
    std::vector<std::unique_ptr<Enemy>> enems;
    std::array<Texture2D, 2>& imgs;
    Vector2 setPoint;
    Button respwanButton;

  public:
    /// @brief membuat world
    World(const std::string& path, std::array<Texture2D, 2>& imgs, Texture2D& healthimg, Texture2D& buttonTexture);
    /// @brief menghapus world
    ~World();
    /** @brief update logika world
     *  @param Reference pauseGame untuk pause game atau tidal
     */ 
    void Update(bool& pauseGame);
    /// @brief draw texture world
    void Draw();
    /// @brief menyimpan data world ke db
    void WritePlayer();
    void WriteEntity();
};

#endif // !WORLD
