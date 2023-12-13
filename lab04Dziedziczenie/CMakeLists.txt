cmake_minimum_required(VERSION 3.27)
project(TEP_lab04Dzieciczenie)

set(CMAKE_CXX_STANDARD 17)

add_executable(TEP_lab04Dzieciczenie main.cpp
        cNode/cNodeOperator/cNodeTrigOperator/cNodeTrigOperator.h
        cNode/cNodeOperator/cNodeTrigOperator/cNodeTrigOperator.cpp
        cNode/cNodeOperator/cNodeArthOperator/cNodeArthOperator.h
        cNode/cNodeOperator/cNodeArthOperator/cNodeArthOperator.cpp
        cNode/cNodeOperator/cNodeOperator.h
        cNode/cNodeLeaf/cNodeLeafVariable/cNodeLeafVariable.h
        cNode/cNodeLeaf/cNodeLeafVariable/cNodeLeafVariable.cpp
        cNode/cNodeLeaf/cNodeLeafNumber/cNodeLeafNumber.h
        cNode/cNodeLeaf/cNodeLeafNumber/cNodeLeafNumber.cpp
        cNode/cNodeLeaf/cNodeLeaf.h
        cNode/cNode.h)
