cmake_minimum_required(VERSION 3.13)

project(clang-finder)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

include(AddLLVM)
include(AddClang)

add_executable(${PROJECT_NAME} finder.cc)

target_link_libraries(${PROJECT_NAME}
  clangTooling
  clangDriver
  clangFrontend
  clangSerialization
  clangParse
  clangSema
  clangEdit
  clangLex
  clangAnalysis
  clangASTMatchers
  clangAST
  clangBasic
  LLVM
  )
