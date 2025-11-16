#pragma once

#include <string>
#include <sqlite3.h>
#include <iostream>
#include <sstream>

namespace DataStore {
    class Database {
    private:
        sqlite3* db;
        std::string db_path;

        bool executeSQL(const std::string& sql) {
            char* errMsg = nullptr;
            int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
                return false;
            }
            return true;
        }

        static int callback(void* data, int argc, char** argv, char** azColName) {
            std::string* result = static_cast<std::string*>(data);
            if (argc > 0 && argv[0]) {
                *result = argv[0];
            }
            return 0;
        }

    public:
        Database(const std::string& path = "") : db(nullptr) {
            if (path == ":memory:") {
                db_path = ":memory:";
            } else {
                db_path = path.empty() ? "electerm_sync.db" : path + "/electerm_sync.db";
            }
            initialize();
        }

        ~Database() {
            if (db) {
                sqlite3_close(db);
            }
        }

        bool initialize() {
            int rc = sqlite3_open(db_path.c_str(), &db);
            if (rc) {
                std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
                return false;
            }

            // Create users table if it doesn't exist
            std::string createTableSQL = R"(
                CREATE TABLE IF NOT EXISTS user_data (
                    user_id TEXT PRIMARY KEY,
                    data TEXT NOT NULL,
                    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
                    updated_at DATETIME DEFAULT CURRENT_TIMESTAMP
                );
            )";

            if (!executeSQL(createTableSQL)) {
                return false;
            }

            // Create index on user_id for faster lookups
            std::string createIndexSQL = R"(
                CREATE INDEX IF NOT EXISTS idx_user_id ON user_data(user_id);
            )";

            return executeSQL(createIndexSQL);
        }

        bool writeData(const std::string& userId, const std::string& jsonData) {
            if (!db) return false;

            // Use UPSERT (INSERT OR REPLACE) to handle both insert and update
            std::string sql = R"(
                INSERT OR REPLACE INTO user_data (user_id, data, updated_at)
                VALUES (?, ?, CURRENT_TIMESTAMP);
            )";

            sqlite3_stmt* stmt;
            int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
                return false;
            }

            // Bind parameters
            sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, jsonData.c_str(), -1, SQLITE_TRANSIENT);

            // Execute
            rc = sqlite3_step(stmt);
            sqlite3_finalize(stmt);

            if (rc != SQLITE_DONE) {
                std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
                return false;
            }

            return true;
        }

        std::string readData(const std::string& userId) {
            if (!db) return "404";

            std::string sql = "SELECT data FROM user_data WHERE user_id = ?;";
            sqlite3_stmt* stmt;
            std::string result = "404";

            int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
                return "404";
            }

            // Bind parameter
            sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);

            // Execute and get result
            rc = sqlite3_step(stmt);
            if (rc == SQLITE_ROW) {
                const unsigned char* data = sqlite3_column_text(stmt, 0);
                if (data) {
                    result = reinterpret_cast<const char*>(data);
                }
            }

            sqlite3_finalize(stmt);
            return result;
        }

        bool deleteData(const std::string& userId) {
            if (!db) return false;

            std::string sql = "DELETE FROM user_data WHERE user_id = ?;";
            sqlite3_stmt* stmt;

            int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
                return false;
            }

            // Bind parameter
            sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);

            // Execute
            rc = sqlite3_step(stmt);
            sqlite3_finalize(stmt);

            return rc == SQLITE_DONE;
        }

        // Get all user IDs (for debugging/admin purposes)
        std::vector<std::string> getAllUsers() {
            std::vector<std::string> users;
            if (!db) return users;

            std::string sql = "SELECT user_id FROM user_data ORDER BY updated_at DESC;";
            sqlite3_stmt* stmt;

            int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
                return users;
            }

            while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
                const unsigned char* userId = sqlite3_column_text(stmt, 0);
                if (userId) {
                    users.push_back(reinterpret_cast<const char*>(userId));
                }
            }

            sqlite3_finalize(stmt);
            return users;
        }
    };

    // Global database instance
    static Database* globalDb = nullptr;

    bool initialize(const std::string& path = "") {
        if (globalDb) {
            delete globalDb;
        }
        globalDb = new Database(path);
        return globalDb->initialize();
    }

    bool writeData(const std::string& userId, const std::string& jsonData) {
        if (!globalDb) return false;
        return globalDb->writeData(userId, jsonData);
    }

    std::string readData(const std::string& userId) {
        if (!globalDb) return "404";
        return globalDb->readData(userId);
    }

    bool deleteData(const std::string& userId) {
        if (!globalDb) return false;
        return globalDb->deleteData(userId);
    }

    std::vector<std::string> getAllUsers() {
        if (!globalDb) return {};
        return globalDb->getAllUsers();
    }
}