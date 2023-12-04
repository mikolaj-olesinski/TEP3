cmake_minimum_required(VERSION 3.26)
project(TEP3)

set(CMAKE_CXX_STANDARD 17)

add_executable(TEP3 main.cpp
        cNode/cNode.h
        cTree/cTree.h
        help-functions-and-constants/stale.h
        help-functions-and-constants/functions.cpp
        help-functions-and-constants/functions.h
        help-functions-and-constants/UI.cpp
)
