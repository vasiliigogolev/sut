cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)
project(sut)



file(GLOB_RECURSE
	SOURCES
		"src/main.cpp"
	)

add_subdirectory(third_party/SDL)
set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/third_party/SDL/include)

add_subdirectory(third_party/SDL_image)
set(SDL_IMAGE_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/third_party/SDL_image)

add_subdirectory(third_party/fmt)
set(FMT_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/third_party/fmt/include)

add_subdirectory(third_party/entt)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image fmt EnTT)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src ${SDL_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIR} ${FMT_INCLUDE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
source_group(TREE "${CMAKE_SOURCE_DIR}/src" FILES ${SOURCES})

if (WIN32)
	add_custom_command(
			TARGET demo POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:demo>"
			VERBATIM
	)

	add_custom_command(
			TARGET demo POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2_image::SDL2_image>" "$<TARGET_FILE_DIR:demo>"
			VERBATIM
	)

	add_custom_command(
			TARGET demo POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:fmt::fmt>" "$<TARGET_FILE_DIR:demo>"
			VERBATIM
	)
endif()