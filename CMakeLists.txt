cmake_minimum_required(VERSION 3.27.3 FATAL_ERROR)

set(PROJECT_NAME Game)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set(GLFW_PATH "external/glfw")
add_subdirectory(${GLFW_PATH})
target_link_libraries(${PROJECT_NAME} glfw)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_PATH}/include)