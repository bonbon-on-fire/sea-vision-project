cmake_minimum_required(VERSION 3.15)
project(sea_vision_step1)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set OpenCV_DIR to local OpenCV
set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/opencv/build)

# find OpenCV
find_package(OpenCV REQUIRED)

# print OpenCV info for debugging
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
message(STATUS "OpenCV include path: ${OpenCV_INCLUDE_DIRS}")

# create executable
add_executable(step main.cpp 
    src/cpp/operations/brightness_operation.cpp
    src/cpp/operations/blur_operation.cpp
)

# link OpenCV
target_link_libraries(step ${OpenCV_LIBS})

# set output directory
set_target_properties(step PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
) 