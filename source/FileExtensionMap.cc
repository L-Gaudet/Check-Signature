#include "FileExtensionMap.h"

FileExtensionMap::FileExtensionMap() {
  std::ifstream file_extensions_file;
  extensions_map = std::unordered_map<std::string, std::string>();
  file_path = "./data/FileExtensions";

  file_extensions_file.open(file_path);

  if (!file_extensions_file) {
    std::cerr << "Error: failed to open FileExtensions file" << std::endl;
    exit(1);
  }

  std::string signature;
  std::string extension;
  // Second line in file is the file extension
  while (getline(file_extensions_file, signature)) {
    getline(file_extensions_file, extension);
    extensions_map[signature] = extension;
  }
}

FileExtensionMap::~FileExtensionMap() {
  extensions_map.clear();
}

std::string FileExtensionMap::get_extension(std::string signature) {
  return extensions_map.find(signature) != extensions_map.end() ? extensions_map[signature] : "";
}