cmake_minimum_required(VERSION 3.25)
set(GOOGLETEST_VERSION 1.15.2)
project(vehicleSimulator VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

set(TEST_DIR
	${CMAKE_CURRENT_LIST_DIR}/test
)

set(SRC_DIR
	${CMAKE_CURRENT_LIST_DIR}/src
)

enable_testing() #to  discover tests in test explorer 
add_subdirectory(googletest) # add googletest subdirectory
include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

# Main project files
add_library(vehicle_info 
    ${CMAKE_CURRENT_LIST_DIR}/src/vehicle_info.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/vehicle_info.hpp
)

add_library(vehicle_simulation 
    ${CMAKE_CURRENT_LIST_DIR}/src/vehicle_simulation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/vehicle_simulation.hpp
)

# Test executable
add_executable(vehicle_simulation_tests
    ${CMAKE_CURRENT_LIST_DIR}/test/test.cpp  # Your test file
    ${CMAKE_CURRENT_LIST_DIR}/src/vehicle_info.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/vehicle_simulation.cpp
)

# Link libraries for tests
target_link_libraries(vehicle_simulation_tests
  PRIVATE
  gtest
  vehicle_info
  vehicle_simulation
)

# Enable testing
enable_testing()
add_test(
  NAME vehicle_simulation_tests
  COMMAND vehicle_simulation_tests
)

add_executable(vehicleSimulator 
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/vehicle_info.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/vehicle_simulation.cpp)
