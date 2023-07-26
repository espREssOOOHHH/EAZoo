cmake_minimum_required(VERSION 3.26)
project(EAZoo)

set(CMAKE_CXX_STANDARD 20)

find_package(Eigen3 3.3 REQUIRED)

file(GLOB_RECURSE source_files src/*.cpp)
add_executable(EAZoo ${source_files})

target_include_directories(${PROJECT_NAME}
        PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(EAZoo
        Eigen3::Eigen)