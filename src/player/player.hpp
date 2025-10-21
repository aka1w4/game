#ifndef PLAYER
#define PLAYER

#include <array>
#include <cstdint>
#include "../../include/raylib/raylib.h"
#include "../entity/entity.hpp"

/// @brief Representasi objek player
class Player {
  private:
    Entity e;                         // struct entity
    uint8_t health, maxHealth;        // darah saat ini dan maksimal darah
    Texture2D* healthimg;             // texture image health
    bool death;

  public:
    /// @brief membuat player baru dengan posisi, arah, dan sprite
    Player(SaveEntity sp, std::array<Texture2D, 2>& imgs, Texture2D& healthimg) : e(Entity{sp.pos, sp.uuid, sp.f, sp.facingright, isIdle, &imgs, sp.count, 4, 16, 32}), health(sp.health), maxHealth(sp.maxHealth), healthimg(&healthimg) {};
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
    void UpdatePos(Vector2& posNew);
    /// @brief draw health player
    void DrawHeart();
    void RespwanPlayer(Vector2& setpoint);
    void Death();
    bool GetPlayerDeath();
};

#endif // !PLAYER
