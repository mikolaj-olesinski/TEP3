cmake_minimum_required(VERSION 3.10)
project(TEP_PREFIX_TREE)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab04
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
        lab05/help-functions-and-constants/CMySmartPointer.h

)

add_executable(lab04Dziedziczenie
        lab04Dziedziczenie/main.cpp
        lab04Dziedziczenie/cTree/cTree.h
        lab04Dziedziczenie/cTree/cTree.cpp
        lab04Dziedziczenie/cNode/cNode.h
        lab04Dziedziczenie/cNode/cNodeArthOperator/cNodeArthOperator.h
        lab04Dziedziczenie/cNode/cNodeNumber/cNodeNumber.h
        lab04Dziedziczenie/cNode/cNodeVariable/cNodeVariable.h
        lab04Dziedziczenie/cNode/cNodeTrigOperator/cNodeTrigOperator.h
        lab04Dziedziczenie/helpFucntions/functions.h
        lab04Dziedziczenie/helpFucntions/functions.cpp
        lab04Dziedziczenie/helpFucntions/stale.h


)


add_executable(lab05
        lab05/main.cpp
        lab05/cTree/cTree.h
        lab05/cTree/cTree.tpp
        lab05/cNode/cNode.h
        lab05/cNode/cNode.cpp
        lab05/help-functions-and-constants/functions.h
        lab05/help-functions-and-constants/functions.cpp
        lab05/help-functions-and-constants/stale.h
        lab05/help-functions-and-constants/UI.h
        lab05/help-functions-and-constants/UI.tpp
        lab05/help-functions-and-constants/CMySmartPointer.h
        lab05/help-functions-and-constants/CRefCounter.h

)

