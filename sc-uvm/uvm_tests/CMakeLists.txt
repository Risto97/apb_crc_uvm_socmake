add_library(uvm_tests INTERFACE)

set(UVM_TESTS 
    simple_test
    )
set_property(TARGET uvm_tests PROPERTY UVM_TESTS ${UVM_TESTS})

foreach(test ${UVM_TESTS})
    target_sources(uvm_tests INTERFACE ${test}.cpp)
endforeach()

target_include_directories(uvm_tests INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    )

