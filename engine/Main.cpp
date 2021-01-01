#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "renderer/VertexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct ShaderProgramSource {

    std::string vertexSource;
    std::string fragmentSource;
};

static ShaderProgramSource parseShader(const std::string& filepath) {

    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream stringStream[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)) {
        
        if(line.find("#sh") != std::string::npos) {

            if(line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }

        } else {
            
            stringStream[(int)type] << line << '\n';
        }
    }

    return {stringStream[0].str(), stringStream[1].str()};
}

static unsigned int compileShader(unsigned int type, const std::string& source) {

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static int createShader(const std::string& vertexShader, const std::string fragmentShader) {
     
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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

    ShaderProgramSource source = parseShader("../engine/res/shaders/basic.sh");
    unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shader);

    // Saving location of uniforms from shader
    int location = glGetUniformLocation(shader, "u_Color");

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.push<float>(2);
    vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

    // Index buffer object Id
    IndexBuffer indexBuffer(indices, 6);

    // Unbinding all buffers (rebind them before drawc all)
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Temp uniform variable
    float red = 0.0f;
    float increment = 0.05f;

    // Main loop
    while(!glfwWindowShouldClose(window)) {

        // Clear buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Binding all objects
        glUseProgram(shader); // Set shader
        glUniform4f(location, red, 0.0f, 0.5f, 1.0f); // Set uniform

        vertexArray.bind();
        indexBuffer.bind(); // Bind index buffer

        // Draw call
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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

    // Clean up shaders
    glDeleteProgram(shader);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}