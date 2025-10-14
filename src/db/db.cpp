#include "db.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <filesystem>
#include "leveldb/db.h"
#include "../entity/entity.hpp"
#include "stduuid/uuid.h"
#include <vector>

void createNewWorld(const std::string& name, unsigned int version, SaveEntity& sp) {
  // membuta directori baru
  std::filesystem::create_directories(std::string(WORLD_NAME) + name);
  // mebuat file level.dat untuk menyimpan metadata world
  std::ofstream levelfile(std::string(WORLD_NAME) + name + "/level.dat", std::ios::binary);
  if (!levelfile) {
    std::cerr << "gagal membuat level.dat" << std::endl;
  }
  // tulis nama world dan level ke level.dat
  uint32_t len = static_cast<uint32_t>(name.size());
  levelfile.write(reinterpret_cast<char*>(&len), sizeof(len));
  levelfile.write(name.c_str(), len);
  levelfile.write(reinterpret_cast<char*>(&version), sizeof(version));
  levelfile.close();
  // membuat database levelDB untuk menyimpan world game
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, std::string(WORLD_NAME) + name + "/db", &db);
  if (!status.ok()) {
    std::cerr << "gagal membuat db: " << status.ToString() << std::endl; 
  }
  // simpan awal data entity player
  status = db->Put(leveldb::WriteOptions(), "player", std::string(reinterpret_cast<char*>(&sp), sizeof(sp)));
  if (!status.ok()) {
    std::cerr << "menyimpan player: " << status.ToString() << std::endl; 
  }
  // delete database leveldb
  delete db; 
}

void readWorldlist::readLevelWorld() {
  // menghapus semua vector yang ada saat ini untuk menyimpan yang baru
  datas.clear();
  // mengecek folder, dan file level.dat
  if (std::filesystem::exists(WORLD_NAME) && std::filesystem::is_directory(WORLD_NAME)) {
    for (const auto& dirEntry : std::filesystem::directory_iterator(WORLD_NAME)) {
      if (std::filesystem::is_directory(dirEntry)) {
        for (const auto& fileEntry : std::filesystem::directory_iterator(dirEntry)) {
          if (std::filesystem::is_regular_file(fileEntry) && fileEntry.path().filename() == "level.dat") {
            std::ifstream in(fileEntry.path().string(), std::ios::binary);
            if (!in) {
              std::cerr << "gagal membaca" << std::endl;
            }
            // membaca nama world, version
            uint32_t len;
            in.read(reinterpret_cast<char*>(&len), sizeof(len));
            std::string name(len, '\0');
            unsigned int version;
            in.read(name.data(), len);
            in.read(reinterpret_cast<char*>(&version), sizeof(version));
            in.close();
            // menyimpan ke worldinfo: name, version, path folder
            datas.push_back(WorldInfo{name, version, dirEntry.path().string()});
          }
        }
      }
    }
  }
}

LoadAndSave::LoadAndSave(const std::string& path) : path(path) {
  // membuat database levelDB baru
  leveldb::Options options;
  leveldb::DB* raw_db = nullptr;
  leveldb::Status status = leveldb::DB::Open(options, std::string(path) + "/db", &raw_db);
  if (!status.ok()) {
    std::cerr << "Gagal buka DB untuk write: " << status.ToString() << std::endl;
  }
  // memasukan raw levedb ke unique_ptr
  dbs.reset(raw_db);
}

void LoadAndSave::writeBinaryPlayer(SaveEntity& sp) {
  // menulis/menyimpan SaveEntity player
  leveldb::Status status = dbs->Put(leveldb::WriteOptions(), "player", std::string(reinterpret_cast<char*>(&sp), sizeof(sp)));
  if (!status.ok()) {
    std::cerr << "menyimpan player: " << status.ToString() << std::endl; 
  }
}

SaveEntity LoadAndSave::readbinaryPlayer() {
  // membaca data "entity" player
  std::string value;
  leveldb::Status status = dbs->Get(leveldb::ReadOptions(), "player", &value);
  if (!status.ok()) {
    std::cerr << "gagal membaca player: " << status.ToString() << std::endl;
  }
  SaveEntity sp;
  // memastikan ukuran data
  if (value.size() == sizeof(sp)) {
    memcpy(&sp, value.data(), sizeof(sp)); // mengkonversi binary ke struct SaveEntity
  }

  return sp; // return SaveEntity
}

void LoadAndSave::writeBinaryEntity(SaveEntity& se) {
  // menulis/menyimpan SaveEntity
  leveldb::Status status = dbs->Put(leveldb::WriteOptions(), "entity-" + uuids::to_string(se.uuid), std::string(reinterpret_cast<char*>(&se), sizeof(se)));
  if (!status.ok()) {
    std::cerr << "menyimpan entity: " << status.ToString() << std::endl; 
  }
}

std::vector<SaveEntity> LoadAndSave::readbinaryEntity() {
  // membaca data "entity" player
  std::vector<SaveEntity> entities;
  leveldb::Iterator* it = dbs->NewIterator(leveldb::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    std::string key = it->key().ToString();
    if (key.rfind("entity-", 0) == 0) {
      const std::string& value = it->value().ToString();
      SaveEntity se;
      memcpy(&se, value.data(), sizeof(se));
      entities.push_back(se);
    }
  }

  delete it;
  return entities; // return SaveEntity
}
