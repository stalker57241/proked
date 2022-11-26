cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(proked VERSION 1.0.00)

configure_file(src/config.hxx.in src/config.hxx)

add_executable(game src/main.cxx)
target_include_directories(game PUBLIC
                            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                            # "$<INSTALL_INTERFACE:include>"
)
