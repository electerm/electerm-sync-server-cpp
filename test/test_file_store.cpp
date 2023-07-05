#include <cassert>
#include "../src/file_store.hpp"

int main() {
    std::string userId = "captch2_test";
    std::string folder_path = "./test_files";
    std::string jsonBody = R"({"key": "value"})";

    // Ensure the test_files directory exists
    if (!fs::is_directory(folder_path)) {
        fs::create_directory(folder_path);
    }

    // Write to file
    bool success = FileStore::writeToFile(jsonBody, userId, folder_path);
    assert(success);

    // Read from file
    std::string result = FileStore::readFromFile(userId, folder_path);
    assert(result == jsonBody);

    // Clean up
    fs::path filePath = FileStore::getFilePath(userId, folder_path);
    fs::remove(filePath);

    return 0;
}
