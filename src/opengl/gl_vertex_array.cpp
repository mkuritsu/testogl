#include "gl_vertex_array.h"
#include <glad/glad.h>

GLVertexArray::GLVertexArray()
{
    glGenVertexArrays(1, &m_Id);
}

GLVertexArray::~GLVertexArray()
{
    glDeleteVertexArrays(1, &m_Id);
}

void GLVertexArray::SetLayout(const VertexLayout& layout) const
{
    uint32_t stride = layout.GetStride();
    uint32_t index = 0;
    size_t offset = 0;
    for (const LayoutElement& elem : layout.GetElements())
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, elem.GetCount(), elem.GetType(), GL_FALSE, stride, (void*) offset);
        offset += elem.GetCount() * elem.GetSize();
        index++;
    }
}

void GLVertexArray::Bind() const
{
    glBindVertexArray(m_Id);
}