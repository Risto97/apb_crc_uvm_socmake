add_ip(apb_agent
    DESCRIPTION "UVM based APB Agent")

ip_sources(${IP} SYSTEMVERILOG
    apb_pkg.sv
    apb_if.sv
    )

ip_include_directories(${IP} SYSTEMVERILOG
    .
    )

ip_link(${IP}
    accellera::sv_uvm::core
    )
