set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_LIST_DIR}/_deps)
set(CPM_DOWNLOAD_VERSION 0.40.2)
include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)

CPMAddPackage(
    NAME SoCMake
    GIT_TAG 54240e1
    GIT_REPOSITORY "git@github.com:HEP-SoC/SoCMake.git"
    )

systemc_build(VERSION 2.3.4 EXACT_VERSION)
uvm_systemc_build(VERSION 1.0-beta6)

CPMAddPackage(
    NAME CRCpp
    GIT_TAG release-1.2.0.0
    GIT_REPOSITORY "https://github.com/d-bahr/CRCpp.git"
    OPTIONS "BUILD_TEST OFF" "BUILD_DOC OFF"
    )
