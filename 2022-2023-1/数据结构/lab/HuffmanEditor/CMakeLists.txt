cmake_minimum_required(VERSION 3.22)
project(HuffmanEditor)

set(CMAKE_CXX_STANDARD 17)

add_executable(HuffmanEditor main.cpp huffman.cpp huffman.h common.h bitmap.cpp bitmap.h)
