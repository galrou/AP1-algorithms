cmake_minimum_required(VERSION 3.15)
project(Ex4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Ex4 main.cpp Server.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.cpp ClientHandler.h CacheManager.cpp CacheManager.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.cpp Solver.h FileCacheManager.cpp FileCacheManager.h StringReverser.cpp StringReverser.h State.h ISearchable.h ISearcher.h Searcher.h MinHeap.h Matrix.h BestFirstSearch.h DepthFirstSearch.h AStar.h BreadhFirstSearch.h MyParallelServer.cpp MyParallelServer.h MyClientHandler.cpp MyClientHandler.h)