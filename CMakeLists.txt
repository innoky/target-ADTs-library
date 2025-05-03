cmake_minimum_required(VERSION 3.10)

project(Lab2SequenceTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/Immutable
    ${CMAKE_SOURCE_DIR}/include/Mutable
    ${CMAKE_SOURCE_DIR}/include/Mutable/Array
    ${CMAKE_SOURCE_DIR}/include/Mutable/List
    ${CMAKE_SOURCE_DIR}/include/core
)

# Добавляем тестовый файл
add_executable(SequenceTest
    test/SequenceTest.cpp
)   

add_executable(SeqUI
    src/Demo.cpp
    src/SequenceUI.cpp
)

add_executable(Server 
    src/StreamServer.cpp
)

add_executable(Client
    src/SenderClient.cpp
)