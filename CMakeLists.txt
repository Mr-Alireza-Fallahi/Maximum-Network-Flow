cmake_minimum_required(VERSION 3.5)

project(Maximum_Network_Flow
    VERSION 0.1
    DESCRIPTION "Create Max Network Flow with Genetic Algorithm"
    LANGUAGES CXX
)
set(Max_Net_Flow maximum_network_flow)

add_executable(${Max_Net_Flow} main.cpp)

target_sources(${Max_Net_Flow} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Graph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Genetic.cpp
)
target_include_directories(${Max_Net_Flow} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(${Max_Net_Flow} PRIVATE cxx_std_11)

