#include <iostream>

#include <GLFW/glfw3.h>

int main() {

    for(int i = 0; i < 10; i++) {
        std::cout << "Coffee rocks!!!" << std::endl;
    }

    // ########## Testing GLFW module... ##########
    
    GLFWwindow *window;

    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(680, 460, "GLFW Window", NULL, NULL);
    if(!window) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Main loop
    while(!glfwWindowShouldClose(window)) {
        //draw();
        //animate();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    // ########## End Testing GLFW module... ##########


    return 0;
}