cmake_minimum_required(VERSION 3.0)
project(VerrouYeah)

SET(INCLUDES "${INCLUDES} ${CMAKE_SOURCE_DIR}/includes")

INCLUDE_DIRECTORIES(INCLUDES)

set(SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/src/models/Backup.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/Data.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/Directory.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/File.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/Frequency.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/Scheduler.cpp 
    ${CMAKE_SOURCE_DIR}/src/models/User.cpp 
    ${CMAKE_SOURCE_DIR}/src/services/ConfigManager.cpp 
    ${CMAKE_SOURCE_DIR}/src/services/Crypt.cpp 
    main.cpp
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")
add_subdirectory(src)
