#pragma once

#include <cstdint>
#include <cstddef>
#include <glad/glad.h>

enum LayoutElementType
{
    FLOAT = GL_FLOAT
};

class LayoutElement
{
public:
    LayoutElement(LayoutElementType type, int32_t count, size_t size);

    int32_t GetCount() const;

    size_t GetSize() const;

    LayoutElementType GetType() const;

private:
    LayoutElementType m_Type;
    int32_t m_Count;
    size_t m_Size;
};