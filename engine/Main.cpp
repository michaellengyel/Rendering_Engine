#include <iostream>

#include "renderer/Renderer.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shader.h"

#include <GLFW/glfw3.h>

int main() {

    GLFWwindow* window;

    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    // Setting the opengl profile to core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(680, 460, "GLFW Window", NULL, NULL);

    if(!window) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Make the window's current context
    glfwMakeContextCurrent(window);

    // Syncronizing buffer swap with monitor refresh rate
    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(EXIT_FAILURE);
    }

    // Log GL verion
    std::cout << "Using GL Version: "<< glGetString(GL_VERSION) << std::endl;

    // Vertex data (buffer)
    float positions[] = {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f  // 3
    };

    // Index buffer
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.push<float>(2);
    vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

    // Index buffer object Id
    IndexBuffer indexBuffer(indices, 6);

    // Saving location of uniforms from shader
    Shader shader("../engine/res/shaders/basic.sh");
    shader.bind();
    shader.setUnifrom4f("u_Color", 0.8f, 0.0f, 0.5f, 1.0f);

    // Unbinding all buffers (rebind them before draw all)
    vertexArray.unBind();
    vertexBuffer.unbind();
    indexBuffer.unbind();
    shader.unBind();

    // Instantiate renderer
    Renderer renderer;

    // Temp uniform variable
    float red = 0.0f;
    float increment = 0.05f;

    // Main loop
    while(!glfwWindowShouldClose(window)) {

        renderer.clear();

        shader.setUnifrom4f("u_Color", red, 0.0f, 0.5f, 1.0f); // Set uniform

        renderer.draw(vertexArray, indexBuffer, shader);

        // Uniforms changing logic
        if (red > 1.0f) {
            increment = -0.05f;
        } else if (red < 0.0f) {
            increment = 0.05f;
        }
        red += increment;

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}