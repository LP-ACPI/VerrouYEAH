project(test_chiffrement)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcrypto -std=c++11")

set(SOURCE_FILES main.cpp crypteur.cpp crypteur.h ../events/events.cpp ../events/events.h)
add_executable(Chiffrement ${SOURCE_FILES})