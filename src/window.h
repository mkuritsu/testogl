#pragma once

#include <string>
#include <SDL3/SDL.h>

class Window
{
public:
    Window();

    Window(const std::string& title, int width, int height);

    void Init();

    void PollEvents();

    bool ShouldQuit() const;

    void Destroy() const;

    void SwapBuffers() const;

    int GetWidth() const;

    int GetHeight() const;

private:
    std::string m_Title;
    int m_Width;
    int m_Height;
    bool m_ShouldQuit = false;
    SDL_Window* m_Window = nullptr;
};