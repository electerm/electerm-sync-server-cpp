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
    .methods("GET"_method, "PUT"_method)
    ([&dt](const crow::request& req) {

        std::string jwt_secret = dt["JWT_SECRET"];
        std::string file_store_path = dt["FILE_STORE_PATH"];
        std::string ids = dt["JWT_USERS"];
        auto token = req.get_header_value("Authorization");
        auto jwt_data = verify_jwt(token.substr(7), jwt_secret, ids); // Strip "Bearer " prefix
        auto str = picojson::value(jwt_data).serialize();

        if (jwt_data.count("id") <= 0) {
            return crow::response(401, str);
        }
        std::string uid = jwt_data["id"].get<std::string>();
        if (req.method == crow::HTTPMethod::Get) {
            auto r = FileStore::readFromFile(uid, file_store_path);
            if (r == "404") {
                return crow::response(404, "404");
            };
            return crow::response(r);
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

    app.port(port).bindaddr(host).run();
    return 0;
}
