cmake_minimum_required(VERSION 3.14)
project(GoFish_)

set(CMAKE_CXX_STANDARD 11)

add_executable(GoFish_ main.cpp card.h card.cpp deck.h deck.cpp player.h player.cpp)