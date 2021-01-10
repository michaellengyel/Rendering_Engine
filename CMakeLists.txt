cmake_minimum_required(VERSION 3.10)

# set the project name
project(Rendering_Engine)

# set the C++ standard
set(CMAKE_CXX_STANDARD 14)

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE ) # TODO: Move to GLEW CMakeLists.txt
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )  # TODO: Move to GLEW CMakeLists.txt
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )  # TODO: Move to GLEW CMakeLists.txt

# adding subdirectories
add_subdirectory(engine)
add_subdirectory(engine/vendor/glew-cmake/build/cmake)

# add the executable
add_executable(${PROJECT_NAME}  engine/Main.cpp 
                                engine/renderer/IndexBuffer.cpp 
                                engine/renderer/VertexBuffer.cpp 
                                engine/renderer/VertexArray.cpp 
                                engine/renderer/Renderer.cpp 
                                engine/renderer/Shader.cpp 
                                engine/renderer/Texture.cpp 
                                engine/statemachine/State.cpp 
                                engine/statemachine/StateClearColor.cpp 
                                engine/statemachine/StateTexture.cpp 
                                engine/vendor/stb_image/stb_image.cpp 
				engine/vendor/imgui/imgui.cpp 
				engine/vendor/imgui/imgui_demo.cpp 
				engine/vendor/imgui/imgui_draw.cpp 
                                engine/vendor/imgui/imgui_widgets.cpp 
                                engine/vendor/imgui/imgui_impl_glfw.cpp 
                                engine/vendor/imgui/imgui_impl_opengl3.cpp 
                                )

# Check dependencies
find_package(OpenGL REQUIRED)

# add include directories
target_include_directories(${PROJECT_NAME} PUBLIC engine/vendor/glew-cmake/include)
target_include_directories(${PROJECT_NAME} PUBLIC engine/vendor/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC engine/vendor)

# add link to directories
target_link_directories(${PROJECT_NAME} PRIVATE engine/vendor/glew/src)
target_link_directories(${PROJECT_NAME} PRIVATE engine/vendor/glfw/src)

# link library to executable
target_link_libraries(${PROJECT_NAME} glew)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL) # TODO: This may need to be removed (legacy req e.g. glBegin())
