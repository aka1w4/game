#include "db.hpp"
#include <fstream>
#include <string>
#include <filesystem>

void createNewWorld(const std::string& name, unsigned int version, SavePlayer& sp) {
  std::filesystem::create_directories(std::string(WORLD_NAME) + name);
  std::ofstream levelfile(std::string(WORLD_NAME) + name + "/level.dat", std::ios::binary);
  if (!levelfile) {
    throw std::runtime_error("gagal menulis level.dat");
  }
  uint32_t len = static_cast<uint32_t>(name.size());
  levelfile.write(reinterpret_cast<char*>(&len), sizeof(len));
  levelfile.write(name.c_str(), len);
  levelfile.write(reinterpret_cast<char*>(&version), sizeof(version));
  levelfile.close();

  std::filesystem::create_directories(std::string(WORLD_NAME) + name + "/db");
  std::ofstream dbfile(std::string(WORLD_NAME) + name + "/db/db.bin", std::ios::binary);
  if (!dbfile) {
     throw std::runtime_error("gagal menulis db file");
  }
  dbfile.write(reinterpret_cast<char*>(&sp.pos), sizeof(sp.pos));
  dbfile.write(reinterpret_cast<char*>(&sp.f), sizeof(sp.f));
  dbfile.write(reinterpret_cast<char*>(&sp.facingright), sizeof(sp.facingright));
  dbfile.close();
}

 void readWorldlist::readLevelWorld() {
  datas.clear();

  if (std::filesystem::exists(WORLD_NAME) && std::filesystem::is_directory(WORLD_NAME)) {
    for (const auto& dirEntry : std::filesystem::directory_iterator(WORLD_NAME)) {
      if (std::filesystem::is_directory(dirEntry)) {
        for (const auto& fileEntry : std::filesystem::directory_iterator(dirEntry)) {
          if (std::filesystem::is_regular_file(fileEntry) && fileEntry.path().filename() == "level.dat") {
            std::ifstream in(fileEntry.path().string(), std::ios::binary);
            if (!in) {
              throw std::runtime_error("gagal membaca");
            }
            uint32_t len;
            in.read(reinterpret_cast<char*>(&len), sizeof(len));
            std::string name(len, '\0');
            unsigned int version;
            in.read(name.data(), len);
            in.read(reinterpret_cast<char*>(&version), sizeof(version));
            in.close();
            datas.push_back(WorldInfo{name, version, dirEntry.path().string()});
          }
        }
      }
    }
  } else {
    std::filesystem::create_directories(WORLD_NAME);
  } 
}

SavePlayer readbinaryPlayer(const std::string& path) {
  SavePlayer ps;
  std::ifstream in(std::string(path) + "/db/db.bin", std::ios::binary);
  if (!in) {
     throw std::runtime_error("gagal membaca");
  }
  in.read(reinterpret_cast<char*>(&ps.pos), sizeof(ps.pos));
  in.read(reinterpret_cast<char*>(&ps.f), sizeof(ps.f));
  in.read(reinterpret_cast<char*>(&ps.facingright), sizeof(ps.facingright));
  in.close();

  return ps;
}

void writeBinaryPlayer(const std::string& path, SavePlayer& sp) {
  std::ofstream out(path + "/db/db.bin", std::ios::binary);
  if (!out) {
     throw std::runtime_error("gagal simpan");
  }
  out.write(reinterpret_cast<char*>(&sp.pos), sizeof(sp.pos));
  out.write(reinterpret_cast<char*>(&sp.f), sizeof(sp.f));
  out.write(reinterpret_cast<char*>(&sp.facingright), sizeof(sp.facingright));
  out.close();
}
