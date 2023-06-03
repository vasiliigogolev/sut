#include "imgui_window.h"
#include "imgui.h"
#include "curl_handler.h"
#include "imgui_stdlib.h"
#include <map>
#include <iostream>

using namespace app;

namespace {
    std::string url;

    std::map<std::string, net::eHttpMethod> methodConverter = {
        { "GET", net::eHttpMethod::GET }
    };
}

void imgui_window::update() {
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

    ImGui::Begin("ImGui Window", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);                          // Create a window called "Hello, world!" and append into it.

    ImGui::InputText("url", &url);

    const char* http_options[] = { "GET", "POST", "DELETE", "PUT" };
    static int item_current_idx = 0;
    const char* combo_preview_value = http_options[item_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
    if (ImGui::BeginCombo("combo 1", combo_preview_value)) {
        for (int n = 0; n < IM_ARRAYSIZE(http_options); n++) {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(http_options[n], is_selected)) {
                item_current_idx = n;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::Button("Send request")) {
        processSendRequest(url, combo_preview_value);
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

void imgui_window::processSendRequest(const std::string& url, const std::string& method) {
    const auto& it = methodConverter.find(method);
    if (it == methodConverter.end()) {
        fprintf(stderr, "processSendRequest: error processing request, couldn't find a method inside of converter map\n");
        return;
    }
    if (url.empty()) {
        fprintf(stderr, "processSendRequest: url is empty");
        return;
    }
    auto methodType = it->second;
    switch (methodType) {
    case net::eHttpMethod::GET:
        net::handler::request_GET(url);
        break;
    default:
        break;
    }
}