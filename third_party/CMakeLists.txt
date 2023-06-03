cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

add_subdirectory(glfw)
add_subdirectory(curl)

file(GLOB IMGUI_SOURCES 
    "${CMAKE_CURRENT_LIST_DIR}/imgui/*.cpp" 
    "${CMAKE_CURRENT_LIST_DIR}/imgui/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/imgui/misc/cpp/*.cpp" 
    "${CMAKE_CURRENT_LIST_DIR}/imgui/misc/cpp/*.h"
    "${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_opengl3.cpp" 
    "${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_opengl3.h" 
    "${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_glfw.cpp" 
    "${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_glfw.h" 
    "${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_opengl3_loader.h"
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_link_libraries(imgui PUBLIC glfw)

target_include_directories(imgui PUBLIC 
    "${CMAKE_CURRENT_LIST_DIR}/imgui" 
    "${CMAKE_CURRENT_LIST_DIR}/imgui/misc/cpp" 
    "${CMAKE_CURRENT_LIST_DIR}/imgui/backends"
)