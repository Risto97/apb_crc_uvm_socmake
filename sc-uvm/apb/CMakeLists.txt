# SPDX-License-Identifier: GPL-3.0-only
# Copyright (c) 2023 Risto Pejašinović CERN
#
# Please retain this header in all redistributions and modifications of the code.

cmake_minimum_required(VERSION 3.25)
project(apb
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "apb UVC"
    )

add_library(${PROJECT_NAME} SHARED
    ${CMAKE_CURRENT_LIST_DIR}/src/apb_agent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/apb_rw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/apb_driver.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/apb_monitor.cpp
    )

target_include_directories(${PROJECT_NAME} PRIVATE
    inc/apb
    )

target_sources(${PROJECT_NAME} PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS inc
    FILES
      inc/uvc_apb.h
      inc/apb/apb_agent.h
      inc/apb/apb_rw.h
      inc/apb/apb_if.h
      inc/apb/apb_modes.h
      inc/apb/apb_driver.h
      inc/apb/apb_monitor.h
      inc/apb/apb_sequencer.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    SystemC::systemc
    UVM-SystemC::shared
    )
#
# # TODO add try compile to check SystemC CXX STANDARD
