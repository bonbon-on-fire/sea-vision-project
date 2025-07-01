cmake_minimum_required(VERSION 3.15)
project(sea_vision_project)

# c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set OpenCV path to local installation
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/opencv/build")
find_package(OpenCV REQUIRED)

# set nlohmann_json path to local installation
set(nlohmann_json_DIR "${CMAKE_SOURCE_DIR}/include/json-develop")
include_directories("${CMAKE_SOURCE_DIR}/include/json-develop/single_include")

# executable
add_executable(sea_vision
    main.cpp
    src/cpp/operations/cpp/base_operation.cpp
    src/cpp/operations/cpp/operations.cpp
    src/cpp/bindings/cpp/pipeline_reader.cpp
    src/cpp/bindings/cpp/operation_factory.cpp
)

# libraries
target_link_libraries(sea_vision
    ${OpenCV_LIBS}
)

# output directory
set_target_properties(sea_vision PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)