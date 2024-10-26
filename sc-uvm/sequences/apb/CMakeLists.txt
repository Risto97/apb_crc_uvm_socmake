
add_library(apb_sequences INTERFACE)

target_sources(apb_sequences INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/base_sequence.cpp"
    )

target_include_directories(apb_sequences INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    )
