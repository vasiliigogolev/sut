cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)
project(sut)
file(GLOB_RECURSE
	SOURCES
		"src/*.cpp"
		"src/*.h"
	)
add_subdirectory(third_party)
add_executable(${PROJECT_NAME} ${SOURCES})

set(ADDITIONAL_LIBS)
if (WIN32)
    list(APPEND ADDITIONAL_LIBS "opengl32")
endif()

target_link_libraries(${PROJECT_NAME} glfw imgui libcurl ${ADDITIONAL_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)