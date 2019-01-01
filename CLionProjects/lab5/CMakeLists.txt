cmake_minimum_required(VERSION 3.10)
project(lab5)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab5 Main.cpp DBentry.h TreeNode.h TreeDB.h DBentry.cpp TreeDB.cpp TreeNode.cpp)