add_executable(Test_Iterpolation Interpolation.cpp )

target_compile_features(Test_Iterpolation PRIVATE cxx_std_20)

target_include_directories(Test_Iterpolation PUBLIC ../../src)

target_link_libraries(Test_Iterpolation PRIVATE src_lib)

set(data_SHADOW ../../res/shaders/basic_vertex.shader ../../res/shaders/basic_fragment.shader)

    foreach(item IN LISTS data_SHADOW)
        message(STATUS ${item})
        add_custom_command(
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
        )
    endforeach()

