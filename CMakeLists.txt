cmake_minimum_required(VERSION 3.3)
project(Sync_AsyncThreadPool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/main/Sync-AsyncThreadPool/SyncQueue.h src/main/Sync-AsyncThreadPool/ThreadPool.h src/main/Sync-AsyncThreadPool/main.cpp)
add_executable(Sync_AsyncThreadPool ${SOURCE_FILES})