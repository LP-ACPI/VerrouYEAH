project(test_events)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES main.cpp events.cpp events.h action.h)
add_executable(Events ${SOURCE_FILES})