#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>

Shader::Shader(const std::string& filePath) : mFilePath(filePath), mRendererId(0) {

    ShaderProgramSource source = parseShader(filePath);
    mRendererId = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() {

    glDeleteProgram(mRendererId);
}

void Shader::bind() const {

    glUseProgram(mRendererId);
}
void Shader::unBind() const {

    glUseProgram(0);
}

void Shader::setUnifrom1i(const std::string& name, int value) {

    glUniform1i(getUniformLocation(name), value);
}


void Shader::setUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3) {

    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

ShaderProgramSource Shader::parseShader(const std::string& filepath) {

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

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {

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

int Shader::createShader(const std::string& vertexShader, const std::string fragmentShader) {
    
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

int Shader::getUniformLocation(const std::string& name) {

    if(mUniformLocationCache.find(name) != mUniformLocationCache.end()) {
        return mUniformLocationCache[name];
    }

    int location = glGetUniformLocation(mRendererId, name.c_str());

    if(location == -1) {
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
    }
    
    mUniformLocationCache[name] = location;
    return location;
}