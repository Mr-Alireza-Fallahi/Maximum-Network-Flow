cmake_minimum_required(VERSION 3.5)

project(Maximum_Network_Flow
    VERSION 0.1
    DESCRIPTION "Create Max Network Flow with Genetic Algorithm"
    LANGUAGES CXX
)

add_executable(Max_Net_Flow
    Node.h
    Node.cpp 
    Graph.h 
    Graph.cpp 
    Genetic.h 
    Genetic.cpp
    main.cpp
)

target_compile_features(Max_Net_Flow PRIVATE cxx_std_11)