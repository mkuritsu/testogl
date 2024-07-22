#include <iostream>
#include "window.h"
#include <glad/glad.h>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <algorithm>
#include "camera.h"
#include <memory>
#include "opengl/gl_program.h"
#include "opengl/gl_buffer.h"
#include "opengl/gl_shader.h"
#include "opengl/gl_texture.h"
#include "opengl/gl_vertex_array.h"
#include "opengl/vertex_layout.h"
#include "opengl/gl_debug.h"

float vertices[] =
{
    // front
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

    // top
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    // bot
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

    // back
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,

    // right
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    // left
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f
};

unsigned int indices[] =
{
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    8, 9, 10, 10, 11, 8,
    12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20
};

static Camera camera;
static std::unique_ptr<GLProgram> s_BasicShader;
static std::unique_ptr<GLVertexArray> s_CubeVAO;
static std::unique_ptr<GLBuffer> s_CubeVBO;
static std::unique_ptr<GLBuffer> s_CubeEBO;
static std::unique_ptr<GLTexture> s_WallTexture;



static void Init(const Window& window)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);

    s_CubeVAO = std::make_unique<GLVertexArray>();
    s_CubeVAO->Bind();

    s_CubeVBO = std::make_unique<GLBuffer>(BufferType::VERTEX_BUFFER);
    s_CubeVBO->Bind();
    s_CubeVBO->SetData(vertices, sizeof(vertices));

    VertexLayout layout;
    layout.PushElement<float>(3);
    layout.PushElement<float>(2);
    layout.PushElement<float>(3);
    s_CubeVAO->SetLayout(layout);

    s_CubeEBO = std::make_unique<GLBuffer>(BufferType::ELEMENT_BUFFER);
    s_CubeEBO->Bind();
    s_CubeEBO->SetData(indices, sizeof(indices));

    s_BasicShader = std::make_unique<GLProgram>();
    GLShader basicVS(ShaderType::VERTEX_SHADER, std::filesystem::path("assets/basic.vert"));
    GLShader basicFS(ShaderType::FRAGMENT_SHADER, std::filesystem::path("assets/basic.frag"));
    s_BasicShader->AttachShader(basicVS);
    s_BasicShader->AttachShader(basicFS);
    s_BasicShader->Link();

    s_BasicShader->SetInt("uTexture0", 0);

    s_WallTexture = std::make_unique<GLTexture>("assets/wall.jpg");
    s_WallTexture->Bind();

    window.CaptureCursor();
    camera.Move(glm::vec3(0.0f, 0.0f, 3.0f));
}

static void Update(Window& window, float delta)
{
    float speed = 10.0f;
    if (window.IsKeyDown(SDL_SCANCODE_ESCAPE))
    {
        window.Quit();
    }
    if (window.IsKeyDown(SDL_SCANCODE_LSHIFT))
    {
        speed *= 2;
    }
    glm::vec3 movement = glm::vec3(0.0f);
    if (window.IsKeyDown(SDL_SCANCODE_W))
    {
        movement += speed * camera.GetFront() * delta;
    }
    if (window.IsKeyDown(SDL_SCANCODE_S))
    {
        movement -= speed * camera.GetFront() * delta;
    }
    if (window.IsKeyDown(SDL_SCANCODE_A))
    {
        movement -= glm::normalize(glm::cross(camera.GetFront(), camera.GetUp())) * speed * delta;
    }
    if (window.IsKeyDown(SDL_SCANCODE_D))
    {
        movement += glm::normalize(glm::cross(camera.GetFront(), camera.GetUp())) * speed * delta;
    }
    camera.Move(camera.GetPosition() + movement);

    MousePos mousePos = window.GetMouse();
    const float sensitivity = 0.05f;
    float mouseX = mousePos.x * sensitivity;
    float mouseY = mousePos.y * sensitivity;
    float yaw = camera.GetYaw();
    float pitch = camera.GetPitch();
    yaw += mouseX;
    pitch = std::clamp(pitch - mouseY, -89.0f, 89.0f);
    camera.SetDirection(yaw, pitch);
    WheelMov wheel = window.GetWheelMov();
    camera.SetFov(camera.GetFov() - wheel.y);
}

static void Draw(float delta)
{
    s_BasicShader->Use();
    s_CubeVAO->Bind();
    s_WallTexture->Bind();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetFov()), 1280.0f / 720.0f, 0.1f, 100.0f);

    glm::mat4 mvp = projection * view * model;
    s_BasicShader->SetMatrix4("uTransform", mvp);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}

int main(int argc, char **argv)
{
    Window window("Test OGL", 1280, 720);
    try 
    {
        window.Init();
    } 
    catch (std::runtime_error e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
        return 1;
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    uint64_t ticks = 0;
    int32_t fps = 0;
    uint64_t lastFrame = 0;
    Init(window);
    while (!window.ShouldQuit())
    {
        uint64_t now = SDL_GetTicks();
        uint64_t frametime = now - lastFrame;
        float delta = frametime / 1000.0f;
        lastFrame = now;
        fps++;
        ticks += frametime;
        if (ticks >= 1000)
        {
            ticks = 0;
            fps = 0;
        }
        window.PollEvents();
        Update(window, delta);
        int width = window.GetWidth();
        int height = window.GetHeight();
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Draw(delta);
        window.SwapBuffers();
    }
    window.Destroy();
    return 0;
}