add_ip(apb_sequences
    DESCRIPTION "UVM sequences for CRC")

ip_include_directories(${IP} SYSTEMVERILOG
    .
    )

ip_link(${IP}
    accellera::sv_uvm::core
    )
