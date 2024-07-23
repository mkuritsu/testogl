#pragma once

#include <cstdint>
#include <vector>
#include "layout_element.h"

class VertexLayout
{
public:

    template<typename T>
    void PushElement(uint32_t count);

    uint32_t GetStride() const;

    const std::vector<LayoutElement>& GetElements() const;

private:
    std::vector<LayoutElement> m_Elements;
    uint32_t m_Stride = 0;
};