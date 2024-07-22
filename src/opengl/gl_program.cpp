#include "gl_program.h"
#include <glad/glad.h>
#include <iostream>

GLProgram::GLProgram() : m_Id(glCreateProgram()) { }

GLProgram::~GLProgram()
{
    glDeleteProgram(m_Id);
}

void GLProgram::AttachShader(const GLShader& shader) const
{
    glAttachShader(m_Id, shader.GetId());
}

void GLProgram::Link() const
{
    glLinkProgram(m_Id);
    int32_t success;
    glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(m_Id, 1024, NULL, infoLog);
        std::cout << "[GLSL] " << infoLog << std::endl;
    }
}

void GLProgram::Use() const
{
    glUseProgram(m_Id);
}

void GLProgram::SetInt(const std::string& identifier, int32_t value) const
{
    Use();
    const char* cString = identifier.c_str();
    int32_t loc = glGetUniformLocation(m_Id, cString);
    glUniform1i(loc, value);
}

void GLProgram::SetMatrix4(const std::string& identifier, const glm::mat4& mat4) const
{
    Use();
    const char* cString = identifier.c_str();
    int32_t loc = glGetUniformLocation(m_Id, cString);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
}