# General info
cmake_minimum_required(VERSION 3.27.5)

set(PROJECT_NAME Cells)
project(${PROJECT_NAME} VERSION 1.1.0 )

# cpp options 
set(CMAKE_CXX_STANDARD 17) 

find_package(SFML 2.6.1 COMPONENTS 
   system window graphics network audio REQUIRED)

add_executable(${PROJECT_NAME} main.cpp CellularAutomaton.cpp DrawAutomaton.cpp)


target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME}  sfml-graphics)