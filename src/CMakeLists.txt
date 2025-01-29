cmake_minimum_required(VERSION 3.5)
project(tictactoe LANGUAGES CXX)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 REQUIRED)

pybind11_add_module(tictactoe game.cpp)
install(TARGETS tictactoe DESTINATION .)