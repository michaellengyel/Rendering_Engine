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

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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

    window = glfwCreateWindow(800, 600, "GLFW Window", NULL, NULL);

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

    /// Implementing Projection Matrix (counteract window distortion (only needs to be set once))
    glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    // Implementing View Matrix
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(1, 0, 0));
    // Implementing Model Matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 0));

    // Calculating Model View Projection Matrix
    glm::mat4 modelViewProjection = projection * view * model;

    // Saving location of uniforms from shader
    Shader shader("../engine/res/shaders/texture.sh");
    shader.bind();
    shader.setUniform4f("u_Color", 0.8f, 0.0f, 0.5f, 1.0f);
    shader.setUniformMat4f("u_ModelViewProjection", modelViewProjection);

    // Adding textures
    Texture texture("../engine/res/images/gray.png");
    texture.bind();
    shader.setUniform1i("u_Texture", 0); // 0 stands for slot 0

    // Unbinding all buffers (rebind them before draw all)
    vertexArray.unBind();
    vertexBuffer.unbind();
    indexBuffer.unbind();
    shader.unBind();

    // Instantiate renderer
    Renderer renderer;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    // Imgui state
    bool show_demo_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Temp uniform variable
    float red = 0.0f;
    float increment = 0.05f;

    // Main loop
    while(!glfwWindowShouldClose(window)) {

        renderer.clear();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        shader.setUniform4f("u_Color", red, 0.0f, 0.5f, 1.0f); // Set uniform

        renderer.draw(vertexArray, indexBuffer, shader);

        // Uniforms changing logic
        if (red > 1.0f) {
            increment = -0.05f;
        } else if (red < 0.0f) {
            increment = 0.05f;
        }
        red += increment;

        // Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        if (show_demo_window)
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Render Imgui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Terminate GLFW
    glfwTerminate();

    return 0;
}