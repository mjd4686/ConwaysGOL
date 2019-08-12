cmake_minimum_required(VERSION 3.1)

project(ConwayGOL)

#find SDL2
find_package(SDL2 REQUIRED)

SET(SRCS src/main.cpp src/GOL.cpp)

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(ConwayGOL ${SRCS})
target_link_libraries(ConwayGOL ${SDL2_LIBRARIES})
target_include_directories(ConwayGOL PUBLIC include)