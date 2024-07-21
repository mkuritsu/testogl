#pragma once

#include <cstdint>
#include <string>
#include <glad/glad.h>
#include <filesystem>

enum ShaderType
{
    VERTEX_SHADER = GL_VERTEX_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

class GLShader
{
public:
    GLShader(ShaderType type, const std::string& source);

    GLShader(ShaderType type, const std::filesystem::path& filePath);

    ~GLShader();

    uint32_t GetId() const;

private:
    ShaderType m_Type;
    uint32_t m_Id;
};

