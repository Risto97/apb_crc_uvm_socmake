cmake_minimum_required(VERSION 3.25)
project(apb_crc_sv_uvm NONE)

include(deps/deps.cmake)

option_boolean(SIM_TRACE "Enable VCD file tracing" OFF)


add_subdirectory("../apb_crc/" "dut")

add_ip(crc_tb_top)

ip_sources(${IP} SYSTEMVERILOG
    crc_tb_top.sv
    )
ip_include_directories(${IP} SYSTEMVERILOG
    .
    )

add_subdirectory(apb)
add_subdirectory(uvm_tests)
add_subdirectory(sequences)
# add_subdirectory(crc_dpi)
ip_link(${IP}
    accellera::sv_uvm::core
    apb_agent 
    apb_sequences
    uvm_tests
    apb_crc

    # crc_dpi
    )


ip_compile_definitions(${IP} SYSTEMVERILOG
    UVM_NO_DPI
    # QUESTA
    # INCA
    # NO_RAND
    )

# modelsim(${IP} 
    # LIBRARY work)

xcelium(${IP}
    XMELAB_ARGS -TIMESCALE 10ns/1ps
    )
# vivado_sim(${IP})

help()
