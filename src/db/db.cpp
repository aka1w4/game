#include "db.hpp"
#include <fstream>
#include <string>
#include <filesystem>

void createNewWorld(const std::string& name, unsigned int version) {
  std::filesystem::create_directories(std::string(WORLD_NAME) + name);
  std::ofstream out(std::string(WORLD_NAME) + name + "/level.dat", std::ios::binary);
  if (!out) {
    throw std::runtime_error("gagal menulis level.dat");
  }
  uint32_t len = static_cast<uint32_t>(name.size());
  out.write(reinterpret_cast<char*>(&len), sizeof(len));
  out.write(name.c_str(), len);
  out.write(reinterpret_cast<char*>(&version), sizeof(version));
  out.close();
}

void readWorldlist::readFolderWorld() {
  datas.clear();

  if (std::filesystem::exists(WORLD_NAME) && std::filesystem::is_directory(WORLD_NAME)) {
    for (const auto& dirEntry : std::filesystem::directory_iterator(WORLD_NAME)) {
      if (std::filesystem::is_directory(dirEntry)) {
        for (const auto& fileEntry : std::filesystem::directory_iterator(dirEntry)) {
          if (std::filesystem::is_regular_file(fileEntry) && fileEntry.path().filename() == "level.dat") {
            datas.push_back(fileEntry.path().string().c_str());
          }
        }
      }
    }
  } else {
    std::filesystem::create_directories(WORLD_NAME);
  } 
}

WorldInfo readWorldlist::readLevelWorld(const char* read_name) {
  uint32_t len;
  std::ifstream in(read_name, std::ios::binary);
  if (!in) {
    throw std::runtime_error("gagal membaca");
  }
  in.read(reinterpret_cast<char*>(&len), sizeof(len));
  std::string name(len, '\0');
  unsigned int version;
  in.read(name.data(), len);
  in.read(reinterpret_cast<char*>(&version), sizeof(version));
  in.close();
  return WorldInfo{name, version};
}
