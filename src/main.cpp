#include <iostream>
#include "window.h"
#include <glad/glad.h>
#include <cstdint>

int main(int argc, char **argv)
{
    Window window("Test OGL", 860, 640);
    window.Init();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    uint64_t ticks = 0;
    int32_t fps = 0;
    int64_t lastFrame = 0;
    while (!window.ShouldQuit())
    {
        uint64_t now = SDL_GetTicks();
        uint64_t frametime = now - lastFrame;
        lastFrame = now;
        fps++;
        ticks += frametime;
        if (ticks >= 1000)
        {
            // std::cout << "FPS: " << fps << std::endl;
            ticks = 0;
            fps = 0;
        }
        window.PollEvents();
        int width = window.GetWidth();
        int height = window.GetHeight();
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        window.SwapBuffers();
    }
    window.Destroy();
    return 0;
}