#ifndef PLAYER
#define PLAYER

#include <array>
#include <raylib.h>
#include <boost/uuid/uuid.hpp>
#include "../entity/entity.hpp"

/// @brief Representasi objek player
class Player {
  private:
    Entity e;

  public:
    /// @brief membuat player baru dengan posisi, arah, dan sprite
    Player(SaveEntity sp, std::array<Texture2D, 2>& imgs, Texture2D& healthimg) : e(Entity{sp.pos, sp.uuid, sp.health, sp.maxHealth, sp.f, sp.facingright, isIdle, &imgs, &healthimg, 0, 4, 16, 32}) {};
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
    SaveEntity GetPlayer();
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
