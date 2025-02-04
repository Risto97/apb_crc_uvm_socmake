add_ip(uvm_tests)

set(UVM_TESTS 
    # simple_test
    )

set_property(TARGET uvm_tests PROPERTY UVM_TESTS ${UVM_TESTS})

ip_include_directories(${IP} SYSTEMVERILOG
    .
    )
