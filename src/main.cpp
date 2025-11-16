#include <crow.h>
#include <jwt-cpp/jwt.h>
#include <picojson/picojson.h>
#include "jwt.hpp"
#include "file_store.hpp"
#include "dotenv.hpp"

#define MSC_COMPATIBLE_SPRINTF(BUFFER_PTR, FORMAT_PTR, VALUE) snprintf((BUFFER_PTR), sizeof(BUFFER_PTR), (FORMAT_PTR), (VALUE))

int main() {
    std::map<std::string, std::string> env = load_dotenv();
    auto& dt = env;
    crow::SimpleApp app;
    std::string port_str = dt["PORT"];
    std::string host = dt["HOST"];
    uint16_t port = static_cast<uint16_t>(std::stoi(port_str));
    CROW_ROUTE(app, "/api/sync")
    .methods("GET"_method, "PUT"_method, "POST"_method)
    ([&dt](const crow::request& req) {

        std::string jwt_secret = dt["JWT_SECRET"];
        std::string file_store_path = dt["FILE_STORE_PATH"];
        std::string ids = dt["JWT_USERS"];
        auto token = req.get_header_value("Authorization");
        auto jwt_data = verify_jwt(token.substr(7), jwt_secret, ids); // Strip "Bearer " prefix

        if (jwt_data.count("error") > 0) {
            std::string error_msg = jwt_data["error"].get<std::string>();
            if (error_msg == "Invalid id") {
                picojson::object res;
                res["status"] = picojson::value("error");
                res["message"] = picojson::value("Unauthorized!");
                return crow::response(401, picojson::value(res).serialize());
            } else {
                picojson::object res;
                res["status"] = picojson::value("error");
                res["message"] = picojson::value("Invalid token");
                return crow::response(422, picojson::value(res).serialize());
            }
        }

        std::string uid = jwt_data["id"].get<std::string>();
        if (req.method == crow::HTTPMethod::Get) {
            auto r = FileStore::readFromFile(uid, file_store_path);
            if (r == "404") {
                return crow::response(404, "File not found");
            };
            return crow::response(r);
        }
        if (req.method == crow::HTTPMethod::Post) {
            return crow::response("test ok");
        }
        if (req.method == crow::HTTPMethod::Put) {
            auto r = FileStore::writeToFile(req.body, uid, file_store_path);
            if (!r) {
                return crow::response(500, "failed");
            }
            return crow::response("ok");
        }

        // Method is other than GET and PUT, which should not happen due to the route configuration
        return crow::response(405);
    });

    CROW_ROUTE(app, "/test")
    .methods("GET"_method)
    ([]() {
        return "ok";
    });

    std::cout << "Electerm sync server starting..." << std::endl;
    std::cout << "Server will be available at: http://" << host << ":" << port << std::endl;
    std::cout << std::endl;
    std::cout << "API Endpoints:" << std::endl;
    std::cout << "  GET  /api/sync  - Retrieve user data (requires JWT auth)" << std::endl;
    std::cout << "  POST /api/sync  - Test endpoint (requires JWT auth)" << std::endl;
    std::cout << "  PUT  /api/sync  - Store user data (requires JWT auth)" << std::endl;
    std::cout << "  GET  /test     - Health check endpoint" << std::endl;
    std::cout << std::endl;
    std::cout << "To use with Electerm:" << std::endl;
    std::cout << "  1. In Electerm sync settings, select 'Custom sync server'" << std::endl;
    std::cout << "  2. Set Server URL: http://" << host << ":" << port << std::endl;
    std::cout << "  3. Set JWT_SECRET: " << dt["JWT_SECRET"] << std::endl;
    std::cout << "  4. Set JWT_USER_NAME: one of [" << dt["JWT_USERS"] << "]" << std::endl;
    std::cout << std::endl;

    app.port(port).bindaddr(host).run();
    return 0;
}
