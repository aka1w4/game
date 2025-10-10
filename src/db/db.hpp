#ifndef GAME_DB
#define GAME_DB

#include <memory>
#include <string>
#include <vector>
#include "../../include/leveldb/db.h"
#include "../entity/entity.hpp"

/// @brief lokasi folder utama untuk menyimpan world
inline std::string_view WORLD_NAME = "world/";
/** @brief membuat world baru
 *  @param path untuk lokasi folder
 *  @param version untuk memasukan versi game di world
 *  @param sp untuk menyimpan data player
 */ 
void createNewWorld(const std::string& path, unsigned int version, SaveEntity& sp);

/// @brief untuk menyimpan informasi world
struct WorldInfo {
    std::string name;
    unsigned int version;
    std::string path;
};

/// @brief untuk membaca dan memnyimpan dalam vector
struct readWorldlist {
  std::vector<WorldInfo> datas;
  void readLevelWorld();
}; 

/// @brief Representasi menulis binary 
class LoadAndSave {
  private:
    std::unique_ptr<leveldb::DB> dbs;
    std::string path;

  public:
    /// @brief membuat write binary baru dengan path world
    LoadAndSave(const std::string& path);
    /** @brief untuk membaca isi world
    *  @param path lokasi folder world yang dituju
    *  @retrun struct SavePlayer berisi posisi, arah 
    */ 
    SaveEntity readbinaryPlayer();
    std::vector<SaveEntity> readbinaryEntity();
    /// @brief menulis ke binary
    void writeBinaryPlayer(SaveEntity& sp);
    void writeBinaryEntity(SaveEntity& se);
};

#endif // !GAME_DB
