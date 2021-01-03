#include <iostream>

#include "renderer/Renderer.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"

#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, 1.0f, 0.0f, // 1
         0.5f,  0.5f, 1.0f, 1.0f, // 2
        -0.5f,  0.5f, 0.0f, 1.0f  // 3
    };

    // Index buffer
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.push<float>(2); // First 2 floats of vertex
    vertexBufferLayout.push<float>(2); // Second 2 floats of vertex
    vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

    // Index buffer object Id
    IndexBuffer indexBuffer(indices, 6);

    // Adding glm prototype code
    glm::mat4 proj = glm::ortho(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

    // Saving location of uniforms from shader
    Shader shader("../engine/res/shaders/texture.sh");
    shader.bind();
    shader.setUnifrom4f("u_Color", 0.8f, 0.0f, 0.5f, 1.0f);

    // Adding textures
    Texture texture("../engine/res/images/gray.png");
    texture.bind();
    shader.setUnifrom1i("u_Texture", 0); // 0 stands for slot 0

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