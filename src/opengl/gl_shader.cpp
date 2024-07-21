#include "gl_shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>

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
    const char* cString = ss.str().c_str();
    glShaderSource(m_Id, 1, &cString, NULL);
    glCompileShader(m_Id);
}

GLShader::~GLShader()
{
    glDeleteShader(m_Id);
}

uint32_t GLShader::GetId() const
{
    return m_Id;
}