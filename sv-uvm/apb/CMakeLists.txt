add_ip(apb_agent
    DESCRIPTION "UVM based APB Agent")

ip_sources(${IP} SYSTEMVERILOG PREPEND
        apb_pkg.sv
        apb_if.sv
        apb_if.sv
        apb_if.sv
    HEADERS
        apb_rw.svh
        apb_monitor.svh
        apb_driver.svh
        apb_agent.svh
        apb_sequencer.svh
        
        
    )

ip_include_directories(${IP} SYSTEMVERILOG
    .
    )

ip_link(${IP}
    accellera::sv_uvm::core
    )
