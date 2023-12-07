cmake_minimum_required(VERSION 3.26.4)
set(PROJECT_NAME GUI_APP)
set(CMAKE_SOURCE_DIR app/src)
set(CMAKE_BINARY_DIR app/build)
set (CMAKE_CXX_STANDARD 23)
message("[x] Building with c++${CMAKE_CXX_STANDARD} standard")


project(${PROJECT_NAME} LANGUAGES CXX)

add_executable(${PROJECT_NAME} app/src/main.cpp)

add_subdirectory(engine engine/bin)
target_link_libraries(${PROJECT_NAME} ENGINE)