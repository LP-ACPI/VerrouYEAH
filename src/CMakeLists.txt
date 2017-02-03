
add_executable(Verrouyeah ${SOURCE_FILES})


target_link_libraries(Verrouyeah crypto)

add_subdirectory(tests)
