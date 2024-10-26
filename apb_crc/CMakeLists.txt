cmake_minimum_required(VERSION 3.25)
project(apb_crc NONE)

add_ip(apb_crc
    DESCRIPTION "Simple APB Linear Feedback Shift Register based random number generator")

ip_sources(apb_crc SYSTEMVERILOG
    ${CMAKE_CURRENT_LIST_DIR}/rtl/apb_crc_core.sv
    ${CMAKE_CURRENT_LIST_DIR}/rtl/apb_crc.sv
    )

ip_sources(apb_crc VERILOG
    ${CMAKE_CURRENT_LIST_DIR}/rtl/lfsr.v
    ${CMAKE_CURRENT_LIST_DIR}/rtl/lfsr_crc.v
    )

ip_sources(${IP} VERILATOR_CFG
    ${PROJECT_SOURCE_DIR}/rtl/verilator_waivers.vlt
    )

ip_sources(apb_crc SYSTEMRDL
    ${CMAKE_CURRENT_LIST_DIR}/apb_crc.rdl
    )

peakrdl_regblock(apb_crc INTF apb4-flat)

if(PROJECT_IS_TOP_LEVEL)
    help()
endif()
