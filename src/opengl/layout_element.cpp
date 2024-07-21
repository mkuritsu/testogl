#include "layout_element.h"

LayoutElement::LayoutElement(LayoutElementType type, int32_t count, size_t size) : m_Type(type), m_Count(count), m_Size(size) { }

int32_t LayoutElement::GetCount() const
{
    return m_Count;
}

size_t LayoutElement::GetSize() const
{
    return m_Size;
}

LayoutElementType LayoutElement::GetType() const
{
    return m_Type;
}
