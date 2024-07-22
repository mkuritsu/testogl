#include "gl_texture.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

GLTexture::GLTexture(const std::filesystem::path& filePath)
{
    glGenTextures(1, &m_Id);
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    std::string str = filePath.string();
    const char* cStr = str.c_str();
    uint8_t* pixels = stbi_load(cStr, &width, &height, &nrChannels, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(pixels);
}

GLTexture::~GLTexture()
{
    glDeleteTextures(1, &m_Id);
}

void GLTexture::Bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_Id);
}