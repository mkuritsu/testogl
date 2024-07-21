#pragma once

#include <cstdint>
#include "vertex_layout.h"

class GLVertexArray
{
public:
    GLVertexArray();

    ~GLVertexArray();

    void SetLayout(const VertexLayout& layout) const;

    void Bind() const;

private:
    uint32_t m_Id;
};