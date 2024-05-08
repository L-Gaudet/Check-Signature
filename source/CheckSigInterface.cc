#include <iostream>
#include <filesystem>
#include <vector>
#include "FileChecker.h"

void check_file(const std::string& path) {
    FileChecker checker;
    bool modified = checker.is_extension_modified(path);
    std::string expected_extension = path.substr(path.find_last_of('.') + 1);
    std::string actual_extension = checker.read_file_extension(checker.read_file_signature(path));

    std::cout << "---------------------------------------\n"
              << "File: " << path << "\n";
    if (modified) {
        std::cout << "Expected Extension: " << expected_extension << "\n"
                  << "Actual Extension: " << actual_extension << "\n";
    }
    
    std::cout << "Modified: " << (modified ? "Yes" : "No") << std::endl;
}

void process_path(const std::filesystem::path& path, bool recursive = false) {
    if (std::filesystem::is_directory(path)) {
        if (recursive) {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
                if (std::filesystem::is_regular_file(entry)) {
                    check_file(entry.path().string());
                }
            }
        } else {
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                if (std::filesystem::is_regular_file(entry)) {
                    check_file(entry.path().string());
                }
            }
        }
    } else if (std::filesystem::is_regular_file(path)) {
        check_file(path.string());
    } else {
        std::cerr << "Error: Invalid path or unsupported file type." << std::endl;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path> [--recursive]" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    bool recursive = (argc > 2 && std::string(argv[2]) == "--recursive");

    process_path(path, recursive);

    return 0;
}
