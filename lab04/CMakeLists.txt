cmake_minimum_required(VERSION 3.10)
project(lab04)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab04
        main.cpp
        cTree/cTree.h
        cTree/cTree.tpp
        cNode/cNode.h
        cNode/cNode.cpp
        help-functions-and-constants/functions.h
        help-functions-and-constants/functions.cpp
        help-functions-and-constants/stale.h
        help-functions-and-constants/UI.h
        help-functions-and-constants/UI.tpp

)

