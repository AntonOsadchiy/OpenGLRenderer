add_executable( renderer main.cpp)

target_compile_features(renderer PRIVATE cxx_std_20)

target_link_libraries(renderer PRIVATE src )

target_include_directories(renderer PUBLIC  ../src/)
