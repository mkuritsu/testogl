#include "gl_program.h"
#include <glad/glad.h>

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
}

void GLProgram::Use() const
{
    glUseProgram(m_Id);
}