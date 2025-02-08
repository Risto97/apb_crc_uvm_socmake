set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_LIST_DIR}/_deps)
set(CPM_DOWNLOAD_VERSION 0.40.2)
include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)

CPMAddPackage(
    NAME  svuvm 
    GIT_TAG master
    GIT_REPOSITORY "https://github.com/HEP-SoC/svuvm-socmake.git"
    OPTIONS "UVM_VERSION 1.2"
            "UVM_DPI ON"
    )

if(NOT SOCMAKE_VERSION)
    CPMAddPackage(
        NAME SoCMake  
        GIT_TAG develop
        GIT_REPOSITORY "https://github.com/HEP-SoC/SoCMake.git"
        )
endif()

set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1) # Remove additional ctest targets
include(CTest)
enable_testing()
