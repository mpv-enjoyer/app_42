#include <drogon/drogon.h>
#include <chrono>
#include "server.h"
using namespace drogon;
using namespace std::chrono_literals;

int app42::echoServer(int argc, char *argv[])
{
    app().registerHandler(
        "/",
        [](const HttpRequestPtr &req,
           std::function<void(const HttpResponsePtr &)> &&callback) {
            HttpResponsePtr resp = HttpResponse::newHttpResponse();
            resp->setBody("root.");
            callback(resp);
        });
    app().registerHandler(
        "/echo",
        [](const HttpRequestPtr &req,
           std::function<void(const HttpResponsePtr &)> &&callback) {
            HttpResponsePtr resp = HttpResponse::newHttpResponse();
            std::string contents = req->getParameter("contents");
            resp->setBody(contents + "\n");
            callback(resp);
        },
        {Post});

    LOG_INFO << "Server running on 0.0.0.0:8848";
    app()
        // All sessions are stored for 24 Hours
        .enableSession(24h)
        .addListener("0.0.0.0", 8848)
        .run();
    return 0;
}