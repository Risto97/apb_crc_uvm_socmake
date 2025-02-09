cmake_minimum_required(VERSION 3.25)
project(apb_crc_sv_uvm NONE)

include(deps/deps.cmake)

option_boolean(SIM_TRACE "Enable VCD file tracing" OFF)
option_enum(SIMULATOR "Which simulator to use" "questa;xcelium;vcs" "xcelium")
option_enum(UVM_VERBOSITY "UVM verbosity level for default target" "UVM_NONE;UVM_LOW;UVM_MEDIUM;UVM_HIGH;UVM_DEBUG" "UVM_MEDIUM")


add_ip(crc_tb_top
    DESCRIPTION "UVM testbench for APB CRC accellerator")

ip_sources(${IP} SYSTEMVERILOG
        crc_tb_top.sv
    HEADERS
        ./scoreboard.svh
        ./env.svh
    )
ip_include_directories(${IP} SYSTEMVERILOG
    .
    )

add_subdirectory("../apb_crc/" "dut")
add_subdirectory(apb)
add_subdirectory(uvm_tests)
add_subdirectory(sequences)
add_subdirectory(crc_dpi)
ip_link(${IP}
    accellera::sv_uvm::core
    apb_agent 
    apb_sequences
    uvm_tests
    apb_crc

    crc_dpi
    )

if(SIMULATOR STREQUAL "xcelium")
    xcelium(${IP}
        SV_COMPILE_ARGS -NOWARN SRCDEPR -NOWARN TSNPK -NOWARN FUNTSK
        ELABORATE_ARGS -TIMESCALE 10ns/1ps
        NO_RUN_TARGET
        )
endif()

if(SIMULATOR STREQUAL "questa")
    modelsim(${IP} QUIET
        NO_RUN_TARGET
        )
endif()

if(SIMULATOR STREQUAL "vcs")
    vcs(${IP}
        ELABORATE_ARGS -ntb_opts uvm
        NO_RUN_TARGET
    )
endif()

# vivado_sim(${IP}
#     NO_RUN_TARGET
#     )

foreach(test ${UVM_TESTS})
    if(SIMULATOR STREQUAL "xcelium")
        xcelium(${IP}
            RUN_ARGS +UVM_TESTNAME=${test}
                     +UVM_VERBOSITY=${UVM_VERBOSITY}
            RUN_TARGET_NAME run_${test}_xcelium
        )
    endif()

    if(SIMULATOR STREQUAL "questa")
        modelsim(${IP} QUIET
            RUN_ARGS +UVM_TESTNAME=${test}
                     +UVM_VERBOSITY=${UVM_VERBOSITY}
            RUN_TARGET_NAME run_${test}_modelsim
        )
    endif() 

    if(SIMULATOR STREQUAL "vcs")
        vcs(${IP}
            RUN_ARGS +UVM_TESTNAME=${test}
                     +UVM_VERBOSITY=${UVM_VERBOSITY}
            RUN_TARGET_NAME run_${test}_vcs
        )
    endif()

    add_test(NAME run_${test}
        COMMAND make run_${test}
        )
endforeach()

help()
