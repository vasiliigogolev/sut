cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)
project(sut)
file(GLOB_RECURSE
	SOURCES
		"src/main.cpp"
	)
add_subdirectory(third_party)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} glfw imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)