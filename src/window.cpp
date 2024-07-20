#include "window.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <exception>
#include <glad/glad.h>

Window::Window() : Window("SDL Window", 1280, 720) {}

Window::Window(const std::string &title, int width, int height) : m_Title(title), m_Width(width), m_Height(height) {}

void Window::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error("Failed to initialize SDL Video!");
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    m_Window = SDL_CreateWindow(m_Title.c_str(), m_Width, m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (m_Window == NULL)
    {
        throw std::runtime_error("Failed to create SDL Window!");
    }
    SDL_GLContext glContext = SDL_GL_CreateContext(m_Window);
    if (glContext == NULL)
    {
        throw std::runtime_error("Failed to initialize OpenGL context!");
    }
    SDL_GL_MakeCurrent(m_Window, glContext);
    SDL_GL_SetSwapInterval(0);
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
    {
        throw std::runtime_error("Failed to initialize glad!");
    }
}

void Window::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        m_DownKeys.clear();
        if (event.type == SDL_EVENT_QUIT)
        {
            m_ShouldQuit = true;
            break;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            m_DownKeys.insert(event.key.key);
        }
    }
}

bool Window::ShouldQuit() const
{
    return m_ShouldQuit;
}

void Window::Destroy() const
{
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Window::SwapBuffers() const
{
    SDL_GL_SwapWindow(m_Window);
}

int Window::GetWidth() const
{
    int width, height;
    SDL_GetWindowSize(m_Window, &width, &height);
    return width;
}

int Window::GetHeight() const
{
    int width, height;
    SDL_GetWindowSize(m_Window, &width, &height);
    return height;
}

bool Window::IsKeyDown(SDL_Keycode key) const
{
    return m_DownKeys.count(key) > 0;
}