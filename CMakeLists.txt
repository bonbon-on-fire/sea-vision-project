cmake_minimum_required(VERSION 3.15)
project(sea_vision_project)

# c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# use Conan toolchain
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# find packages from Conan
find_package(nlohmann_json REQUIRED)

# executable
add_executable(sea_vision
    main.cpp
    src/cpp/operations/cpp/base_operation.cpp
    src/cpp/operations/cpp/operations.cpp
    src/cpp/bindings/cpp/pipeline_reader.cpp
    src/cpp/bindings/cpp/operation_factory.cpp
)

# link libraries from Conan
target_link_libraries(sea_vision
    ${OpenCV_LIBS}
    nlohmann_json::nlohmann_json
)

target_include_directories(sea_vision PRIVATE src/cpp)
target_include_directories(sea_vision PRIVATE opencv-4.11.0/include)

# output directory
set_target_properties(sea_vision PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)