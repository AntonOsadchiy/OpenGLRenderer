add_executable( renderer main.cpp)

target_compile_features(renderer PRIVATE cxx_std_20)

target_include_directories(renderer PUBLIC ../src/)

target_link_libraries(renderer PRIVATE src_lib )

target_include_directories(renderer PRIVATE ../external/assimp/include/)

add_compile_definitions(RES_PATH="${CMAKE_SOURCE_DIR}/res")