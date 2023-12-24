cmake_minimum_required(VERSION 3.10)
project(TEP_PREFIX_TREE)

set(CMAKE_CXX_STANDARD 14)


add_executable(lab01
        lab01/*.h
        lab01/CTable.cpp
        lab01/CTable.h
        lab01/functions.cpp
        lab01/functions.h
        lab01/main.cpp
)

add_executable(lab02
        lab02/CNumber.cpp
        lab02/CNumber.h
        lab02/CNumberOperations.cpp
        lab02/main.cpp
)

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

)

