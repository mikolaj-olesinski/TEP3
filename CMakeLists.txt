cmake_minimum_required(VERSION 3.10)
project(TEP_PREFIX_TREE)

set(CMAKE_CXX_STANDARD 14)

add_executable(TEP_PREFIX_TREE
        lab04/main.cpp
        lab04/cTree/cTree.h
        lab04/cTree/cTree.tpp
        lab04/cNode/cNode.h
        lab04/cNode/cNode.cpp
        lab04/help-functions-and-constants/functions.h
        lab04/help-functions-and-constants/functions.cpp
        lab04/help-functions-and-constants/stale.h
        lab04/help-functions-and-constants/UI.h
        lab04/help-functions-and-constants/UI.tpp
)