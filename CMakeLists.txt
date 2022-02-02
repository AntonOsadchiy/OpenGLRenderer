cmake_minimum_required(VERSION 3.19)
project(OpenGLRenderer VERSION 1.0  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_subdirectory(app)

add_subdirectory(external/glfw)

add_definitions(-DGLEW_STATIC)
add_subdirectory(external/glew)

find_package(OpenGL REQUIRED)

target_link_libraries(src glfw opengl32 libglew_static ${GLFW_LIBRARIES})