#pragma once

#include <cstdint>
#include "gl_shader.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLProgram
{
public:
    GLProgram();

    ~GLProgram();

    void AttachShader(const GLShader& shader) const;

    void Link() const;

    void Use() const;

    void SetInt(const std::string& identifier, int32_t value) const;

    void SetMatrix4(const std::string& identifier, const glm::mat4& mat4) const;

    void SetVec3(const std::string& identifier, const glm::vec3& vec3) const;

    void SetFloat(const std::string& identifier, float value) const;

private:
    uint32_t m_Id;
};