#pragma once
#include <string>

namespace app {
    class imgui_window {
    public:
        static void update();
    private:
        static void processSendRequest(const std::string& url, const std::string& method);
    };
}

namespace net {
    enum class eHttpMethod {
        GET
    };
}