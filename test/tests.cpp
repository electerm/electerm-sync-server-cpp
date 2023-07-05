#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() function.
#include "catch.hpp"

#include "file_store.h"

using namespace FileStore;

TEST_CASE("Test getFilePath", "[file_store]") {
    fs::path filePath = getFilePath("user1234", "/tmp");
    REQUIRE(filePath.string() == "/tmp/user1234.json");
}

TEST_CASE("Test writeToFile and readFromFile", "[file_store]") {
    std::string userId = "user1234";
    std::string folder_path = "/tmp";
    std::string jsonBody = "{\"key\": \"value\"}";

    // Clean up any previous test files.
    fs::path filePath = getFilePath(userId, folder_path);
    fs::remove(filePath);

    // Test writing to a file.
    REQUIRE(writeToFile(jsonBody, userId, folder_path) == true);

    // Test reading from a file.
    std::string fileContent = readFromFile(userId, folder_path);
    REQUIRE(fileContent == jsonBody);

    // Clean up the test file.
    fs::remove(filePath);
}
