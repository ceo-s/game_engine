cmake_minimum_required(VERSION 3.26.4)
set(PROJECT_NAME ENGINE)

project(${PROJECT_NAME} LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED
        engine.h
        src/application.h
        src/application.cpp
        src/entryPoint.h
)

if(UNIX AND NOT APPLE)
    target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC .)
