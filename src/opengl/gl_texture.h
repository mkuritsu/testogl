#pragma once

#include <cstdint>
#include <filesystem>

class GLTexture
{
public:

    GLTexture(const std::filesystem::path& filePath);

    ~GLTexture();

    void Bind(uint32_t slot = 0) const;

private:
    uint32_t m_Id;
};