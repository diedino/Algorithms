cmake_minimum_required(VERSION 3.12)
project(KDZ)

set(CMAKE_CXX_STANDARD 14)

add_executable(KDZ src/main.cpp src/Dinic/Dinic.cpp src/Dinic/Dinic.h src/Edmond_Carp/Edmond_Karp.cpp src/Edmond_Carp/Edmond_Karp.h src/Ford_Fulkerson/Ford_Fulkerson.cpp src/Ford_Fulkerson/Ford_Fulkerson.h)