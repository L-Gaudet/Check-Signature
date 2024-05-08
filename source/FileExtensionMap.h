#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unordered_map>

class FileExtensionMap {
  public:
    FileExtensionMap();
    ~FileExtensionMap();
    std::string get_extension(std::string signature);
    
  private:
    std::unordered_map<std::string, std::string> extensions_map;
    std::string file_path;
    
};