project(verrouyeah)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcrypto -std=c++11")

set(SOURCE_FILES main.cpp models/Crypt.cpp models/Crypt.h models/User.cpp models/User.h models/json.h models/Config.cpp models/Config.h)
add_executable(Verrouyeah ${SOURCE_FILES})