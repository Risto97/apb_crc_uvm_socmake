cmake_minimum_required(VERSION 3.25)
project(dpi_test CXX)

include(deps/deps.cmake)

add_library(crc_dpi SHARED
    ./crc_dpi.cpp
    )

target_link_libraries(crc_dpi PRIVATE
    CRCpp
    )

# target_compile_options(crc_dpi PRIVATE -m32)
# target_link_options(crc_dpi PRIVATE -m32)
