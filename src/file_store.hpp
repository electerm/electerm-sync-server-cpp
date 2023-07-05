#pragma once

#include <string>
#include <fstream>
#include <picojson/picojson.h>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace FileStore {
    fs::path getFilePath(const std::string& userId, const std::string& folder_path) {
        fs::path folder = folder_path.empty() ? fs::current_path() : fs::path(folder_path);
        return folder / (userId + ".json");
    }

    bool writeToFile(const std::string& jsonBody, const std::string& userId, const std::string& folder_path = "") {
        fs::path filePath = getFilePath(userId, folder_path);
        std::ofstream file(filePath.string());

        if (!file.is_open()) {
            return false;
        }

        file << jsonBody;
        file.close();

        return true;
    }

    std::string readFromFile(const std::string& userId, const std::string& folder_path = "") {
        picojson::value jsonResult;
        fs::path filePath = getFilePath(userId, folder_path);

        if (!fs::is_regular_file(filePath)) {
            return "404";
        }

        std::ifstream file(filePath.string());

        if (!file.is_open()) {
            return "404";
        }

        std::string fileContent((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        file.close();

        std::string err = picojson::parse(jsonResult, fileContent);

        if (!err.empty()) {
            return "404";
        }

        return fileContent;
    }
}
