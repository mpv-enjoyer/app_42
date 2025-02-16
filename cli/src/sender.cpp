#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <sstream>
#include "sender.h"

static const char* SERVER_URL = "127.0.0.1:8848";

std::string app42::send(std::string key, std::string value)
{
    std::stringstream output;
    try {
        std::string request_field = std::string("{\"") + key + std::string("\":\"") + value + std::string("\"}");
        curlpp::Easy request;
        // Setting the URL to retrive.
        request.setOpt(new curlpp::options::Url(SERVER_URL));
        request.setOpt(new curlpp::options::HttpHeader({std::string("Content-Type: application/json")}));
        request.setOpt(new curlpp::options::PostFields(request_field));
        request.setOpt(new curlpp::options::PostFieldSize(request_field.size()));
        output << request;
    }
    catch ( curlpp::LogicError & e ) {
        output << e.what();
    }
    catch ( curlpp::RuntimeError & e ) {
        output << e.what();
    }
    return output.str();
}