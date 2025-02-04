cmake_minimum_required(VERSION 3.25)
project(apb_crc NONE)

option_boolean(SYNTHESIS "Create synthesis targets" OFF)

include(deps/deps.cmake)

add_ip(apb_crc
    DESCRIPTION "Simple APB Linear Feedback Shift Register based random number generator")

ip_sources(apb_crc SYSTEMVERILOG
    rtl/apb_crc_core.sv
    rtl/apb_crc.sv
    )

ip_sources(${IP} VERILATOR_CFG
    rtl/verilator_waivers.vlt
    )

ip_sources(${IP} SYSTEMRDL
    apb_crc.rdl
    )

ip_link(${IP}
    alexforencich::ip::lfsr
    )

peakrdl_regblock(apb_crc INTF apb4-flat)

if(SYNTHESIS)
    sv2v(${IP} REPLACE)
    yosys(${IP} REPLACE)
endif()

if(PROJECT_IS_TOP_LEVEL)
    help()
endif()
