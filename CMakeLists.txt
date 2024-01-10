cmake_minimum_required(VERSION 3.27.3 FATAL_ERROR)

set(PROJECT_NAME Game)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/game/game.cpp
	src/game/game.h
	src/game/tank.cpp
	src/game/tank.h
	src/renderer/animatedsprite.cpp
	src/renderer/animatedsprite.h
	src/renderer/ebo.cpp
	src/renderer/ebo.h
	src/renderer/shaderprogram.cpp
	src/renderer/shaderprogram.h
	src/renderer/sprite.cpp
	src/renderer/sprite.h
	src/renderer/texture2d.cpp
	src/renderer/texture2d.h
	src/renderer/vao.cpp
	src/renderer/vao.h
	src/renderer/vbo.cpp
	src/renderer/vbo.h
	src/renderer/vbolayout.cpp
	src/renderer/vbolayout.h
	src/resources/resourcemanager.cpp
	src/resources/resourcemanager.h
	src/resources/stb_image.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

target_include_directories(${PROJECT_NAME} PUBLIC external)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)