#include "gl_buffer.h"
#include <glad/glad.h>

GLBuffer::GLBuffer(BufferType type)
{
    glGenBuffers(1, &m_Id);
    switch (type)
    {
    case VERTEX_BUFFER:
        m_Target = GL_ARRAY_BUFFER;
        break;

    case ELEMENT_BUFFER:
        m_Target = GL_ELEMENT_ARRAY_BUFFER;
        break;
    }
}

GLBuffer::~GLBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

void GLBuffer::Bind() const
{
    glBindBuffer(m_Target, m_Id);
}

void GLBuffer::SetData(const void* data, size_t size) const
{
    Bind();
    glBufferData(m_Target, size, data, GL_STATIC_DRAW);
}