#include "FileChecker.h"

FileExtensionMap FileChecker::extension_map;

FileChecker::FileChecker() {}

FileChecker::~FileChecker() {}

bool FileChecker::is_extension_modified(std::string filename) {
  std::string expected_file_extension = filename.substr(filename.find_last_of('.') + 1);
  std::string actual_file_extension = read_file_extension(read_file_signature(filename));

  if (expected_file_extension.length() == actual_file_extension.length()) {
    return expected_file_extension != actual_file_extension;
  } 
  else if (actual_file_extension.find(" " + expected_file_extension + " ") != std::string::npos
          || actual_file_extension.find(expected_file_extension + " ") != std::string::npos
          || actual_file_extension.find(" " + expected_file_extension) != std::string::npos) {
    return false;
  } 
  else {
    return true;
  }
}

std::string FileChecker::read_file_extension(std::string file_signature) {
  std::string file_extension = extension_map.get_extension(file_signature);
  return file_extension.empty() ? "txt binary or unkown file extension." : file_extension;
}

std::string FileChecker::read_file_signature(std::string filename) {
  std::ifstream file;
  file.open(filename, std::ios::binary);

  if (!file) {
    std::cerr << "Error: failed to open file" << std::endl;
    return "";
  }
  
  const size_t num_bytes = 4; // number of bytes to read to get file signature
  unsigned char buffer[num_bytes];

  file.read(reinterpret_cast<char*>(buffer), num_bytes);

  if (!file) {
    std::cerr << "Error: failed to read file signature" << std::endl;
    return "";
  }

  std::ostringstream oss;

  // Convert each byte to hexadecimal
  for (std::size_t i = 0; i < num_bytes; ++i) {
      oss << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << static_cast<int>(buffer[i]);
  }

  return oss.str();
}

std::vector<std::string> FileChecker::read_files(std::vector<std::string> file_names) {
  std::vector<std::string> file_extensions;

  for (size_t i = 0; i < file_names.size(); ++i) {
    std::string file_signature = read_file_signature(file_names[i]);
    std::string file_extension = read_file_extension(file_signature);
    file_extensions.push_back(file_extension);
  }
  return file_extensions;
}

std::vector<std::string> FileChecker::read_directory(const char* directory) {
  std::vector<std::string> file_names;

  for (const auto& entry : std::filesystem::directory_iterator(directory)) {
      if (entry.is_regular_file()) {
          file_names.push_back(entry.path().string());
      }
  }
  return FileChecker::read_files(file_names);
}

std::vector<std::vector<std::string>> FileChecker::read_directory_recursive(const char* directory) {
  std::vector<std::vector<std::string>> file_extensions;
  // scan each file in the directory
  // gather the subdirectory names
  // call read_directory_recursive on each subdirectory
    // append the results of each to the file_extensions vector

  for (const auto& entry : std::filesystem::directory_iterator(directory)) {
      if (entry.is_regular_file()) {
          std::vector<std::string> file_names;
          file_names.push_back(entry.path().string());
          file_extensions.push_back(FileChecker::read_files(file_names));
      }
  }
  return file_extensions;
}