add_ip(uvm_tests
    DESCRIPTION "UVM Tests for CRC")

ip_sources(uvm_tests SYSTEMVERILOG
    HEADERS
        ./base_test.svh
    )

ip_include_directories(${IP} SYSTEMVERILOG
    .
    )

ip_link(${IP}
    accellera::sv_uvm::core
    )


set(UVM_TESTS 
    simple_test
    smoke_test
    )

set_property(TARGET uvm_tests PROPERTY UVM_TESTS ${UVM_TESTS})

set(UVM_TESTS ${UVM_TESTS} PARENT_SCOPE)
