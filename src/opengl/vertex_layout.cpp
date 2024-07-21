#include "vertex_layout.h"

uint32_t VertexLayout::GetStride() const
{
    return m_Stride;
}

const std::vector<LayoutElement>& VertexLayout::GetElements() const
{
    return m_Elements;
}