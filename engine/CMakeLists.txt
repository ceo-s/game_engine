cmake_minimum_required(VERSION 3.26.4)
set(PROJECT_NAME ENGINE)
set (CMAKE_CXX_STANDARD 23)

project(${PROJECT_NAME} LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED
        engine.h
        src/application.h
        src/application.cpp
        src/entryPoint.h
        src/logger.h
        src/logger.cpp
        src/events/event.h
        src/events/events.h
        src/events/keyEvents.h
        src/events/mouseEvents.h
        src/events/windowEvents.h
        src/events/appEvents.h
        src/window.h
        platform/linux/window.h
        platform/linux/window.cpp
        src/layers/layer.h
        src/layers/layerStack.h
        src/layers/layers.h
        src/layers/imguiLayer.cpp
        src/layers/imguiLayer.h
        src/input.cpp
        src/input.h
)


#if(UNIX AND NOT APPLE)
target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)
#endif()

target_sources(${PROJECT_NAME} PUBLIC src/pch/pch.cpp)
target_precompile_headers(${PROJECT_NAME} PUBLIC src/pch/pch.cpp)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)


add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/imgui)
target_link_libraries(${PROJECT_NAME} imgui)

target_include_directories(${PROJECT_NAME} PUBLIC external/spdlog/include)
target_include_directories(${PROJECT_NAME} PUBLIC .)
