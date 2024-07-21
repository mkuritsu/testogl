#pragma once

#include <cstdint>
#include "gl_shader.h"

class GLProgram
{
public:
    GLProgram();

    ~GLProgram();

    void AttachShader(const GLShader& shader) const;

    void Link() const;

    void Use() const;

private:
    uint32_t m_Id;
};