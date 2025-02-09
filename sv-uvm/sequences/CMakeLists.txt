add_ip(apb_sequences
    DESCRIPTION "UVM sequences for CRC")

ip_sources(apb_sequences SYSTEMVERILOG
    HEADERS
        ./simple_sequence.svh
    )

ip_include_directories(${IP} SYSTEMVERILOG
    .
    )

ip_link(${IP}
    accellera::sv_uvm::core
    )
