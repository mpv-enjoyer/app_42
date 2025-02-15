#include <trantor/utils/Logger.h>
#ifdef _WIN32
#include <ws2tcpip.h>
#else
#include <netinet/tcp.h>
#include <sys/socket.h>
#endif

#include <drogon/drogon.h>
using namespace drogon;

int main()
{
    // `registerHandler()` adds a handler to the desired path. The handler is
    // responsible for generating a HTTP response upon an HTTP request being
    // sent to Drogon
    app().registerHandler(
        "/",
        [](const HttpRequestPtr &request,
           std::function<void(const HttpResponsePtr &)> &&callback) {
            LOG_INFO << "connected:"
                     << (request->connected() ? "true" : "false");
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("Hello, World!");
            callback(resp);
        },
        {Get});
    app()
        .setBeforeListenSockOptCallback([](int fd) {
            LOG_INFO << "setBeforeListenSockOptCallback:" << fd;
#ifdef _WIN32
#elif __linux__
            int enable = 1;
            if (setsockopt(
                    fd, IPPROTO_TCP, TCP_FASTOPEN, &enable, sizeof(enable)) ==
                -1)
            {
                LOG_INFO << "setsockopt TCP_FASTOPEN failed";
            }
#else
#endif
        })
        .setAfterAcceptSockOptCallback([](int) {});
    app().addListener("127.0.0.1", 8848).run();
}