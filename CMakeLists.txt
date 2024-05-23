cmake_minimum_required(VERSION 3.27)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(untitled1
        main.cpp)

find_package(MAVSDK REQUIRED)
target_link_libraries(untitled1
        MAVSDK::mavsdk
)

if(NOT MSVC)
    add_compile_options(offboard PRIVATE -Wall -Wextra)
else()
    add_compile_options(offboard PRIVATE -WX -W2)
endif()

if(MINGW OR MSVC)
    # For M_PI
    add_target_definitions(offboard "-D_USE_MATH_DEFINES")
endif()
