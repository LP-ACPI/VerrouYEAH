cmake_minimum_required(VERSION 3.0)
project(VerrouYeah)

SET(INCLUDES "${INCLUDES} ${CMAKE_SOURCE_DIR}/includes")

if (WIN32)
    SET(INCLUDES "${INCLUDES} ${CMAKE_SOURCE_DIR}/utilities/opensslWin64")
endif (WIN32)

INCLUDE_DIRECTORIES(INCLUDES)

set(SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/src/models/Backup.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/Data.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/Directory.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/File.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/Frequency.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/Scheduler.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/User.cpp 
    ${CMAKE_SOURCE_DIR}/src/services/Config.cpp 
    ${CMAKE_SOURCE_DIR}/src/services/Crypt.cpp 
    main.cpp
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(src)
