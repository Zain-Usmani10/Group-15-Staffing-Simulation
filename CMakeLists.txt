cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(group-15-staffing-simulation LANGUAGES CXX)
include(CMake/CPM.cmake)
CPMAddPackage("gh:nlohmann/json@3.11.2")

add_executable(group-15-staffing-simulation 
    Customer_List.cpp 
    customer.cpp
)
target_link_libraries(group-15-staffing-simulation PRIVATE nlohmann_json::nlohmann_json)