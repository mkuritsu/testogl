#pragma once

#include <cstdint>
#include <cstddef>

enum BufferType
{
    VERTEX_BUFFER,
    ELEMENT_BUFFER
};

class GLBuffer
{

public:
    GLBuffer(BufferType type);

    ~GLBuffer();

    void Bind() const;

    void SetData(const void* data, size_t size) const;

private:
    uint32_t m_Target;
    uint32_t m_Id;
};