cmake_minimum_required(VERSION 3.10)

# set the project name
project(Rendering_Engine)

# set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# adding subdirectories
add_subdirectory(engine)

# add the executable
add_executable(${PROJECT_NAME} engine/Main.cpp)
