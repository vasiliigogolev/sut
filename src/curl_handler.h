#pragma once
#include <string>

namespace net {
    class handler {
    public:
        static void request_GET(const std::string& url);
    };
}