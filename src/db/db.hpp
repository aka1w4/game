#ifndef DB
#define DB

#include <string>
#include <vector>

inline std::string_view WORLD_NAME = "world/";
void createNewWorld(const std::string&, unsigned int version);

struct WorldInfo {
    std::string name;
    unsigned int version;
};

struct readWorldlist {
  std::vector<std::string> datas;
  void readFolderWorld();
  WorldInfo readLevelWorld(const char*);
}; 

#endif // !DB
