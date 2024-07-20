#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <unordered_set>

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

    float GetDelta() const;

    bool IsKeyDown(SDL_Keycode key) const;

private:
    std::string m_Title;
    int m_Width;
    int m_Height;
    bool m_ShouldQuit = false;
    SDL_Window* m_Window = nullptr;
    std::unordered_set<SDL_Keycode> m_DownKeys;
};