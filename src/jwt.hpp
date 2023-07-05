// This is an include guard, which prevents this file from being included multiple times
#include <jwt-cpp/jwt.h>
#ifndef jwt_HPP
#define jwt_HPP

jwt::traits::kazuho_picojson::object_type verify_jwt(const std::string& token, const std::string& secret) {
    try {
        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256{secret});
        auto decoded = jwt::decode(token);
        verifier.verify(decoded);
        auto payload_json = decoded.get_payload_json();
        
        if (payload_json.count("id") > 0 && payload_json["id"].is<std::string>() && payload_json["id"].get<std::string>() == "user1") {
            // crow::json::wvalue wclaims;
            // for (const auto& claim : payload_json.items()) {
            //     wclaims[claim.key()] = claim.value().dump();
            // }
            return payload_json;
        } else {
            jwt::traits::kazuho_picojson::object_type res;
            res["error"] = picojson::value("Invalid id");
            return res;
        }
    } catch (const std::exception& e) {
        jwt::traits::kazuho_picojson::object_type res;
        res["error"] = picojson::value(e.what());
        return res;
    }
}

#endif