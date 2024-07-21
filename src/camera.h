#pragma once

#include <glm/glm.hpp>

class Camera
{
public:

    void Move(float x, float y, float z);
    
    void Move(const glm::vec3 vec);

    void SetDirection(float yaw, float pitch);

    float GetYaw() const;
    
    float GetPitch() const;

    float GetFov() const;

    void SetFov(float fov);

    glm::mat4 GetViewMatrix() const;

    glm::vec3 GetFront() const;

    glm::vec3 GetUp() const;

    glm::vec3 GetPosition() const;

private:
    glm::vec3 m_Position = glm::vec3(0.0f);
    glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
    float m_Yaw = -90.0f;
    float m_Pitch = 0.0f;
    float m_Fov = 45.0f;
};