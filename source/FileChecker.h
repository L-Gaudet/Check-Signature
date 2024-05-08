#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <sstream>
#include <string>
#include <filesystem>
#include <vector>
#include "FileExtensionMap.h"

class FileChecker {
  public:
    FileChecker();
    ~FileChecker();
    static bool is_extension_modified(std::string filename);
    static std::string read_file_extension(std::string file_signature);
    static std::string read_file_signature(std::string filename);
    static std::vector<std::string> read_files(std::vector<std::string> file_names);
    static std::vector<std::string> read_directory(const char* directory);
    static std::vector<std::vector<std::string>> read_directory_recursive(const char* directory);
  private:
    static FileExtensionMap extension_map;
};
