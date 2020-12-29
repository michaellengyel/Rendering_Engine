#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(EXIT_FAILURE);
    }

    std::cout << "Using GL Version: "<< glGetString(GL_VERSION) << std::endl;

    unsigned int vao = 0;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertex and Fragment shader

    // Vertex data
    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    ShaderProgramSource source = parseShader("../basic.sh");
    //std::cout << source.vertexSource << std::endl;
    //std::cout << source.fragmentSource << std::endl;
    //std::cout << "End Test" << std::endl;

    unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shader);

    unsigned int bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

    // Main loop
    while(!glfwWindowShouldClose(window)) {

        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

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