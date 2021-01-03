//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

//============================================================================================================
// Class Trivia
//============================================================================================================

struct ShaderProgramSource {

    std::string vertexSource;
    std::string fragmentSource;
};

class Shader {
public:

    Shader(const std::string& filePath);

    ~Shader();

    void bind() const;

    void unBind() const;

    // Set uniforms
    
    void setUniform1i(const std::string& name, int value);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniformMat4f(const std::string& name, const glm::mat4 matrix);

private:

    unsigned int mRendererId;

    std::string mFilePath;

    std::unordered_map<std::string, int> mUniformLocationCache;

    ShaderProgramSource parseShader(const std::string& filepath);

    unsigned int compileShader(unsigned int type, const std::string& source);

    int createShader(const std::string& vertexShader, const std::string fragmentShader);

    int getUniformLocation(const std::string& name);

};