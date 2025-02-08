set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.25)
project(apb_crc_sc_uvm CXX)

include(deps/deps.cmake)

option_boolean(SIM_TRACE "Enable VCD file tracing" OFF)

add_subdirectory("../apb_crc/" "dut")

if(SIM_TRACE)
    set(VLT_TRACE_ARG --trace --trace-structs)
endif()

verilator(apb_crc SYSTEMC
    VERILATOR_ARGS --pins-sc-uint ${VLT_TRACE_ARG} -Wno-fatal -O3
    )

add_executable(${PROJECT_NAME}
    sc_main.cpp
    env.cpp
    scoreboard.cpp
    )
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}
    )

add_subdirectory(apb)
add_subdirectory(uvm_tests)
add_subdirectory(sequences)

target_link_libraries(${PROJECT_NAME} PRIVATE
    # External libraries
    SystemC::systemc
    UVM-SystemC::shared
    CRCpp
    clipp::clipp

    # Internal UVM components
    apb
    uvm_tests
    sequences

    # Verilated HDL
    apb_crc__vlt
    )

target_compile_options(${PROJECT_NAME} PUBLIC
    -O3
    )

if(SIM_TRACE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC TRACE VERILATOR)
endif()

enable_testing()
foreach(test IN LISTS UVM_TESTS)
    add_test(NAME ${test} COMMAND ./apb_crc_sc_uvm --UVM-TEST ${test})
endforeach()

help()
