cmake_minimum_required(VERSION 3.10)
project(layout)

set(CMAKE_CXX_STANDARD 14)

add_executable(layout
        main.cpp
        components/component_brush.cpp
        components/component_frame.cpp
        components/component_list.cpp
        )

target_compile_definitions(layout PRIVATE -DSDL_MAIN_HANDLED)
target_link_libraries(layout PRIVATE SDL2)