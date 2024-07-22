#include "gl_debug.h"
#include <iostream>

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    std::cout << "[OPENGL] (" << id << ") " << message << std::endl;
}