#include "db.hpp"
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string>
#include <filesystem>

void createNewWorld(const std::string& name, unsigned int version) {
  std::filesystem::create_directories(std::string("world/") + name);
  std::ofstream out(std::string("world/") + name + "/level.dat", std::ios::binary);
  if (!out) {
    throw std::runtime_error("error in create world");
  }
  out.write(name.c_str(), name.size());
  out.write(reinterpret_cast<char*>(&version), sizeof(version));
  out.close();
}
