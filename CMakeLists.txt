cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests test.cpp LinkedList.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} Threads::Threads)