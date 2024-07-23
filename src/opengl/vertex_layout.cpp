#include "vertex_layout.h"

uint32_t VertexLayout::GetStride() const
{
    return m_Stride;
}

const std::vector<LayoutElement>& VertexLayout::GetElements() const
{
    return m_Elements;
}

template<>
void VertexLayout::PushElement<float>(uint32_t count)
{
    m_Elements.emplace_back(FLOAT, count, sizeof(float));
    m_Stride += count * sizeof(float);
}