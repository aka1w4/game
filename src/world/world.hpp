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

/// @brief Representasi dunia baru
class NewWorld {
  private:
    std::unique_ptr<Textinput> textinput_name;                  // smart pointer textinput untuk mengelola instance text
    std::unique_ptr<Button> submit;                             // smart pointer button untuk membuat dunia baru
    std::function<void(SavePlayer&, const std::string&)> play;  // untuk menjalankan permainan

  public:
    /// @brief membuat dunia baru
    NewWorld(Texture2D& inputT, Texture2D& buttonT, std::function<void(SavePlayer&, const std::string&)> p);
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
    Camera2D cam;                                                 // kamera utama untuk mengatur posisi tampilan game
    std::unique_ptr<Map> m;                                       // smart pointer mengelola instance map
    std::chrono::time_point<std::chrono::steady_clock> lastSave;  // waktu terakhir menyimpan
    WriteBinary wb;                                               // untuk menulis data binary

  public:
    /// @brief membuat world
    World(SavePlayer& sp, const std::string& path, std::array<Texture2D, 2>& imgs, Texture2D& healthimg);
    /// @brief menghapus world
    ~World();
    /** @brief update logika world
     *  @param Reference pauseGame untuk pause game atau tidal
     */ 
    void Update(bool& pauseGame);
    /// @brief draw texture world
    void Draw();
    /// @brief menyimpan data world ke db
    void WriteWorld();
};

#endif // !WORLD
