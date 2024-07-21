#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <unordered_set>

struct MousePos
{
    float x, y;
};

typedef MousePos WheelMov;

class Window
{
public:
    Window();

    Window(const std::string& title, int width, int height);

    void Init();

    void PollEvents();

    bool ShouldQuit() const;

    void Quit();

    void Destroy() const;

    void SwapBuffers() const;

    int GetWidth() const;

    int GetHeight() const;

    float GetDelta() const;

    bool IsKeyDown(SDL_Keycode key) const;

    MousePos GetMouse() const;

    MousePos GetWheelMov() const;

    float GetTime() const;

    void CaptureCursor() const;

private:
    std::string m_Title;
    int m_Width;
    int m_Height;
    bool m_ShouldQuit = false;
    WheelMov m_WheelMov;
    SDL_Window* m_Window = nullptr;
};