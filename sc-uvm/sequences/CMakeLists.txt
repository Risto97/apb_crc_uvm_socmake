add_library(sequences INTERFACE
    )

target_include_directories(sequences INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    )

add_subdirectory(apb)


target_link_libraries(sequences INTERFACE apb_sequences)


