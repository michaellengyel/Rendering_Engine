cmake_minimum_required(VERSION 3.10)

# set the project name
project(Rendering_Engine)

# set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# adding subdirectories
add_subdirectory(engine)

# add the executable
add_executable(${PROJECT_NAME} engine/Main.cpp)

# Check dependencies
find_package(OpenGL REQUIRED)

# add include directories
target_include_directories(${PROJECT_NAME} PUBLIC engine/vendor/glfw/include)

# add link to directories
target_link_directories(${PROJECT_NAME} PRIVATE engine/vendor/glfw/src)

# link library to executable
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL) # This may need to be removed (legacy req e.g. glBegin())