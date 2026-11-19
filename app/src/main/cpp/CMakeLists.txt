cmake_minimum_required(VERSION 3.22.1)
project("pfengine")

add_library(
        pfengine
        SHARED
        jni_bridge.cpp
)

find_library(log-lib log)
target_link_libraries(pfengine ${log-lib})
