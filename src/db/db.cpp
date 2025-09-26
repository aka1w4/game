#include "db.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include "../../inlcude/leveldb/db.h"

void createNewWorld(const std::string& name, unsigned int version, SavePlayer& sp) {
  std::filesystem::create_directories(std::string(WORLD_NAME) + name);
  std::ofstream levelfile(std::string(WORLD_NAME) + name + "/level.dat", std::ios::binary);
  if (!levelfile) {
    std::cerr << "gagal membuat level.dat" << std::endl;
  }
  uint32_t len = static_cast<uint32_t>(name.size());
  levelfile.write(reinterpret_cast<char*>(&len), sizeof(len));
  levelfile.write(name.c_str(), len);
  levelfile.write(reinterpret_cast<char*>(&version), sizeof(version));
  levelfile.close();

  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, std::string(WORLD_NAME) + name + "/db", &db);
  if (!status.ok()) {
    std::cerr << "gagal membuat db: " << status.ToString() << std::endl; 
  }

  status = db->Put(leveldb::WriteOptions(), "player", std::string(reinterpret_cast<char*>(&sp), sizeof(sp)));
  if (!status.ok()) {
    std::cerr << "menyimpan player: " << status.ToString() << std::endl; 
  }

  delete db;
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
              std::cerr << "gagal membaca" << std::endl;
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
  leveldb::DB* db;
  leveldb::Options options;
  leveldb::Status status = leveldb::DB::Open(options, std::string(path) + "/db", &db);
  if (!status.ok()) {
    std::cerr << "Gagal buka DB untuk read: " << status.ToString() << std::endl;
  }

  std::string value;
  status = db->Get(leveldb::ReadOptions(), "player", &value);
  if (!status.ok()) {
    std::cerr << "gagal membaca player: " << status.ToString() << std::endl;
  }
  SavePlayer sp;
  if (value.size() == sizeof(sp)) {
    memcpy(&sp, value.data(), sizeof(sp));
  }

  delete db;
  return sp;
}

void writeBinaryPlayer(const std::string& path, SavePlayer& sp) {
  leveldb::DB* db;
  leveldb::Options options;
  leveldb::Status status = leveldb::DB::Open(options, std::string(path) + "/db", &db);
  if (!status.ok()) {
    std::cerr << "Gagal buka DB untuk write: " << status.ToString() << std::endl;
  }

  status = db->Put(leveldb::WriteOptions(), "player", std::string(reinterpret_cast<char*>(&sp), sizeof(sp)));
  if (!status.ok()) {
    std::cerr << "menyimpan player: " << status.ToString() << std::endl; 
  }

  delete db;
}
