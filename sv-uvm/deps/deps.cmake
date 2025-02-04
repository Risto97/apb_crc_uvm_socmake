set(UVM_VERSION 1.2)
include("/tools/work/sv_uvm_socmake/CMakeLists.txt")

if(NOT SOCMAKE_VERSION)
    CPMAddPackage(
        NAME SoCMake  
        GIT_TAG develop
        GIT_REPOSITORY "https://github.com/HEP-SoC/SoCMake.git"
        )
endif()

