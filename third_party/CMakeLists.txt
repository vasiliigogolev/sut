cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

add_subdirectory(glfw)

file(GLOB IMGUI_SOURCES "${CMAKE_CURRENT_LIST_DIR}/imgui/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/imgui/*.h")

message(STATUS ${IMGUI_SOURCES})

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_LIST_DIR}/imgui")