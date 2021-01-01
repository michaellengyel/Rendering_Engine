//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#pragma once

#include <string>
#include <unordered_map>

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
    void setUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3);

private:

    unsigned int mRendererId;

    std::string mFilePath;

    std::unordered_map<std::string, int> mUniformLocationCache;

    ShaderProgramSource parseShader(const std::string& filepath);

    unsigned int compileShader(unsigned int type, const std::string& source);

    int createShader(const std::string& vertexShader, const std::string fragmentShader);

    unsigned int getUniformLocation(const std::string& name);

};