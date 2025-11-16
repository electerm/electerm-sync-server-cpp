#include "../src/data_store.hpp"
#include <cassert>
#include <iostream>
#include <string>

void test_database_operations() {
    // Test with in-memory database for testing
    DataStore::Database db(":memory:");

    std::string testUser = "test_user";
    std::string testData = "{\"key\": \"value\", \"number\": 42}";

    // Test write operation
    bool writeResult = db.writeData(testUser, testData);
    assert(writeResult == true);
    std::cout << "✓ Write operation successful" << std::endl;

    // Test read operation
    std::string readResult = db.readData(testUser);
    assert(readResult == testData);
    std::cout << "✓ Read operation successful" << std::endl;

    // Test read non-existent user
    std::string nonExistentResult = db.readData("non_existent_user");
    assert(nonExistentResult == "404");
    std::cout << "✓ Read non-existent user returns 404" << std::endl;

    // Test update operation
    std::string updatedData = "{\"key\": \"updated_value\", \"number\": 100}";
    bool updateResult = db.writeData(testUser, updatedData);
    assert(updateResult == true);
    std::cout << "✓ Update operation successful" << std::endl;

    // Verify update
    std::string updatedReadResult = db.readData(testUser);
    assert(updatedReadResult == updatedData);
    std::cout << "✓ Update verification successful" << std::endl;

    // Test delete operation
    bool deleteResult = db.deleteData(testUser);
    assert(deleteResult == true);
    std::cout << "✓ Delete operation successful" << std::endl;

    // Verify deletion
    std::string deletedReadResult = db.readData(testUser);
    assert(deletedReadResult == "404");
    std::cout << "✓ Delete verification successful" << std::endl;

    // Test multiple users
    std::string user1 = "user1";
    std::string user2 = "user2";
    std::string data1 = "{\"user\": \"one\"}";
    std::string data2 = "{\"user\": \"two\"}";

    db.writeData(user1, data1);
    db.writeData(user2, data2);

    assert(db.readData(user1) == data1);
    assert(db.readData(user2) == data2);
    std::cout << "✓ Multiple users isolation successful" << std::endl;
}

int main() {
    std::cout << "Running DataStore tests..." << std::endl;

    try {
        test_database_operations();
        std::cout << "\n🎉 All tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}