#include <drogon/drogon.h>
#include <chrono>

#include "server.h"
#include "calculator.h"

using namespace drogon;
using namespace std::chrono_literals;

void app42::echoServer(int argc, char *argv[])
{
    app().registerHandler(
        "/",
        [](const HttpRequestPtr &req,
           std::function<void(const HttpResponsePtr &)> &&callback) {
            Json::Value json;
            if (req->getJsonObject() == nullptr)
            {
                json["err"] = "No json in this request";
                return callback(HttpResponse::newHttpJsonResponse(json));
            }
            if (req->getJsonObject()->isMember("exp"))
            {
                auto contents = req->getJsonObject()->operator[]("exp").asString();
                try
                {
                    json["res"] = std::to_string(int(app42::Calculator(contents).value()));
                }
                catch(const std::exception& e)
                {
                    json["err"] = e.what();
                }
            }
            if (req->getJsonObject()->isMember("cmd"))
            {
                auto contents = req->getJsonObject()->operator[]("cmd").asString();
                try
                {
                    json["res"] = contents;
                }
                catch(const std::exception& e)
                {
                    json["err"] = e.what();
                }
            }
            callback(HttpResponse::newHttpJsonResponse(json));
        },
        {Post});
    LOG_INFO << "Server running on 0.0.0.0:8848";
    app()
        // All sessions are stored for 24 Hours
        .enableSession(24h)
        .addListener("0.0.0.0", 8848)
        .run();
}