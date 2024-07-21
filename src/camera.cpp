#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::Move(float x, float y, float z)
{
    Move(glm::vec3(x, y, z));
}
    
void Camera::Move(const glm::vec3 vec)
{
    m_Position += vec;
}

float Camera::GetYaw() const
{
    return m_Yaw;
}

void Camera::SetDirection(float yaw, float pitch)
{
    m_Yaw = yaw;
    m_Pitch = pitch;
    float x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    float y = sin(glm::radians(pitch));
    float z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_Front = glm::normalize(glm::vec3(x, y, z));
}
    
float Camera::GetPitch() const
{
    return m_Pitch;
}

float Camera::GetFov() const
{
    return m_Fov;
}

void Camera::SetFov(float fov)
{
    m_Fov = fov;
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}