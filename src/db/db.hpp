#ifndef GAME_DB
#define GAME_DB

#include <memory>
#include <string>
#include <vector>
#include "../../inlcude/leveldb/db.h"
#include "../player/player.hpp"

inline std::string_view WORLD_NAME = "world/";
void createNewWorld(const std::string&, unsigned int version, SavePlayer& sp);
SavePlayer readbinaryPlayer(const std::string& path);

struct WorldInfo {
    std::string name;
    unsigned int version;
    std::string path;
};

struct readWorldlist {
  std::vector<WorldInfo> datas;
  void readLevelWorld();
}; 

class WriteBinary {
  private:
    std::unique_ptr<leveldb::DB> dbs;
    std::string path;

  public:
    WriteBinary(const std::string& path);
    void writeBinaryPlayer(SavePlayer& sp);
};

#endif // !GAME_DB
