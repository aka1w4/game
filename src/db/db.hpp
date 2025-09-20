#ifndef DB
#define DB

#include <string>
#include <vector>
#include "../player/player.hpp"

inline std::string_view WORLD_NAME = "world/";
void createNewWorld(const std::string&, unsigned int version);
void writeBinPlayer(const std::string&, SavePlayer& sp);
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

#endif // !DB
