cmake_minimum_required(VERSION 3.19)
project(OpenGLRenderer VERSION 1.0  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_subdirectory(app)

add_subdirectory(external/glfw)
find_package(OpenGL REQUIRED)

find_package(GLEW 2.0 REQUIRED)

target_link_libraries(src glfw opengl32 GLEW::GLEW ${GLFW_LIBRARIES})