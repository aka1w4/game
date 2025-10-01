#ifndef PLAYER
#define PLAYER

#include <array>
#include <raylib.h>
#include <boost/uuid/uuid.hpp>

/// @brief Arah hadap player (digunakan untuk animasi atau pergerakan)
enum Focus {
  Down,
  DownLeft,
  Left,
  UpLeft,
  Up,
};

/// @brief Status gerak player
enum MoveState {
  isIdle,
  isWalk,
};

/// @brief data yang disave/diload 
struct SavePlayer {
  Vector2 pos;
  Focus f;
  bool facingright;
  int health, maxHealth;
  boost::uuids::uuid uuid;
};

/// @brief Representasi objek player
class Player {
  private:
    Vector2 pos;                      // posisi saat ini
    std::array<Texture2D, 2>* imgs;   // pointer array sprite image player
    unsigned int count;               // pinghitungan frame
    Focus f = Down;                   // Arah player saat ini
    MoveState ms;                     // status gerak player saat ini
    bool facingright;                 // arah hadap ke kanan
    int frameCount = 4;               // jumlah frame animasi
    int frameWidth = 16;              // lebar sprite per frame
    int frameHeight = 32;             // tinggi sprite per frame
    int health, maxHealth;            // darah saat ini dan maksumal darah
    Texture2D* healthimg;             // texture image health
    boost::uuids::uuid uuid;          // identitas player

  public:
    /// @brief membuat player baru dengan posisi, arah, dan sprite
    Player(SavePlayer sp, std::array<Texture2D, 2>& imgs, Texture2D& healthimg);
    /// @brief update logika player
    void Update();
    /// @brief draw sprite player
    void Draw();
    /** @brief pindah posisi player
     *  @param dx perubahan posisi x
     *  @param dy perubahan posisi y 
     *  @param newFocus perubahan arah hadap baru
     *  @param right perubahan apakah menghadap kanan
     */
    void Move(float dx, float dy, Focus newFocus, bool right);
    /// @brief mengambil data dalam bentuk SavePlayer untuk diload/save
    SavePlayer GetPlayer();
    /// @brief  Dapatkan posisi player saat ini
    const Vector2& GetPlayerpos();
    /// @brief Rectangle player
    const Rectangle GetRec();
    /// @brief update posisi player
    void UpdatePos(Vector2 posNew);
    /// @brief draw health player
    void DrawHeart();
};

#endif // !PLAYER
