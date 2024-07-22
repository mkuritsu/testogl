#include "gl_shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

GLShader::GLShader(ShaderType type, const std::string& source) : m_Type(type), m_Id(glCreateShader(type))
{
    const char* cString = source.c_str();
    glShaderSource(m_Id, 1, &cString, NULL);
    glCompileShader(m_Id);
}

GLShader::GLShader(ShaderType type, const std::filesystem::path& filePath) : m_Type(type), m_Id(glCreateShader(type))
{
    std::ifstream file(filePath);
    std::stringstream ss;
    ss << file.rdbuf();
    std::string str = ss.str();
    const char* cString = str.c_str();
    glShaderSource(m_Id, 1, &cString, NULL);
    glCompileShader(m_Id);
    int32_t success;
    glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(m_Id, 1024, NULL, infoLog);
        std::cout << "[GLSL] " << infoLog << std::endl;
    }
}

GLShader::~GLShader()
{
    glDeleteShader(m_Id);
}

uint32_t GLShader::GetId() const
{
    return m_Id;
}