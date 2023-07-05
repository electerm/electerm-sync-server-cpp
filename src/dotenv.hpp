#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace fs = boost::filesystem;

std::map<std::string, std::string> load_dotenv() {
    fs::path current_path = fs::current_path();
    fs::path dotenv_path = current_path / ".env";
    std::ifstream file(dotenv_path.string()); // Convert the path to a string before passing it to the ifstream constructor
    std::map<std::string, std::string> env_map;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t equal_pos = line.find('=');
            if (equal_pos != std::string::npos) {
                std::string key = line.substr(0, equal_pos);
                std::string value = line.substr(equal_pos + 1);
                env_map[key] = value;
            }
        }
    } else {
        std::cerr << "Error: Could not open the .env file. Please make sure the file exists and has the correct permissions." << std::endl;
    }
    return env_map;
}
