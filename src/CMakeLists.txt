add_executable(Verrouyeah ${SOURCE_FILES})

if (WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/utilities/opensslWin64)
    target_link_libraries(Verrouyeah eay32)
endif (WIN32)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcrypto")
endif (UNIX)

add_subdirectory(tests)
