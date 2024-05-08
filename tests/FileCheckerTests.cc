#include "../source/FileChecker.h"
#include <gtest/gtest.h>

class FileCheckerTest : public ::testing::Test {
protected:
    FileChecker file_checker;
};

TEST_F(FileCheckerTest, ReadTxtFile) {
    std::string file_name = "test-files/file.txt";
    std::string expected_file_signature = "74686973";
    std::string expected_file_extension = "txt binary or unkown file extension.";

    std::string actual_file_signature = file_checker.read_file_signature(file_name);
    std::string actual_file_extension = file_checker.read_file_extension(actual_file_signature);

    EXPECT_EQ(actual_file_signature, expected_file_signature);
    EXPECT_EQ(actual_file_extension, expected_file_extension);
}

TEST_F(FileCheckerTest, ReadZipFile) {
    std::string file_name = "test-files/5.zip";
    std::string expected_file_signature = "504B0304";
    std::string expected_file_extension = "zip aar apk docx epub jar kmz msix odp ods odt pk3 pk4 pptx usdz vsdx xlsx";

    std::string actual_file_signature = file_checker.read_file_signature(file_name);
    std::string actual_file_extension = file_checker.read_file_extension(actual_file_signature);

    EXPECT_EQ(actual_file_signature, expected_file_signature);
    EXPECT_EQ(actual_file_extension, expected_file_extension);
}

TEST_F(FileCheckerTest, ReadNonExistentFile) {
    std::string file_name = "nonexistent.file";
    std::string actual_file_signature = file_checker.read_file_signature(file_name);
    EXPECT_EQ(actual_file_signature, "");
}

TEST_F(FileCheckerTest, ReadMultipleFiles) {
    std::vector<std::string> file_names = {"test-files/5.zip", "test-files/file.txt"};
    std::vector<std::string> actual_file_extensions = file_checker.read_files(file_names);
    std::vector<std::string> expected_file_extensions = {"zip aar apk docx epub jar kmz msix odp ods odt pk3 pk4 pptx usdz vsdx xlsx", "txt binary or unkown file extension."};
    EXPECT_EQ(actual_file_extensions, expected_file_extensions);
}

TEST_F(FileCheckerTest, ReadDirectory) {
    const char* directory = "test-files";
    std::vector<std::string> actual_file_extensions = file_checker.read_directory(directory);
    std::vector<std::string> expected_file_extensions = {"txt binary or unkown file extension.", "zip aar apk docx epub jar kmz msix odp ods odt pk3 pk4 pptx usdz vsdx xlsx", "jpg", "zip aar apk docx epub jar kmz msix odp ods odt pk3 pk4 pptx usdz vsdx xlsx"};
    EXPECT_EQ(actual_file_extensions, expected_file_extensions);
}

TEST_F(FileCheckerTest, ReadDirectoryRecursive) {
    const char* directory = "test-files";
    std::vector<std::vector<std::string>> actual_file_extensions = file_checker.read_directory_recursive(directory);
    std::vector<std::vector<std::string>> expected_file_extensions = {{"txt binary or unkown file extension.", "zip aar apk docx epub jar kmz msix odp ods odt pk3 pk4 pptx usdz vsdx xlsx", "jpg"}, {"zip aar apk docx epub jar kmz msix odp ods odt pk3 pk4 pptx usdz vsdx xlsx"}};
    EXPECT_EQ(actual_file_extensions, expected_file_extensions);
}

TEST_F(FileCheckerTest, ExtensionNotModified) {
    std::string file = "test-files/5.zip";
    bool actual_is_extension_modified = file_checker.is_extension_modified(file);
    EXPECT_EQ(actual_is_extension_modified, false);
}

TEST_F(FileCheckerTest, ExtensionIsModified) {
    std::string file = "test-files/5.modified";
    std::cout << "supposed extension: " << file.substr(file.find_last_of('.') + 1) << std::endl;
    bool actual_is_extension_modified = file_checker.is_extension_modified(file);
    EXPECT_EQ(actual_is_extension_modified, true);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
