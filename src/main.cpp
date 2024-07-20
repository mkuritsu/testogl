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

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = 
{
    0, 1, 3,
    1, 2, 3
};

static uint32_t vbo;
static uint32_t vao;
static uint32_t ebo;
static uint32_t shaderProgram;
static uint32_t textures[2];

static uint32_t LoadShader(const std::string& path, GLenum shaderType)
{
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    std::string source = ss.str();
    const char* sourceStr = source.c_str();
    uint32_t shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &sourceStr, NULL);
    glCompileShader(shader);
    return shader;
}

static uint32_t LoadTexture(const std::string& path, int texSlot)
{
    uint32_t tex;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0 + texSlot);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    uint8_t* pixels = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    // glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pixels);
    return tex;
}

static void Init()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    int32_t stride = 8 * sizeof(float);
    glEnableVertexAttribArray(0); // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(1); // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,stride, (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(2); //texcoords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    shaderProgram = glCreateProgram();
    uint32_t vertexShader = LoadShader("assets/basic.vert", GL_VERTEX_SHADER);
    uint32_t fragmentShader = LoadShader("assets/basic.frag", GL_FRAGMENT_SHADER);
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    textures[0] = LoadTexture("assets/container.jpg", 0);
    textures[1] = LoadTexture("assets/awesomeface.png", 1);
    glUniform1i(glGetUniformLocation(shaderProgram, "uTexture0"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "uTexture1"), 1);
}

static void Draw(float delta)
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);

    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 mvp = projection * view * model;

    // transform = glm::rotate(transform, glm::radians(delta * 10), glm::vec3(0.0, 0.0, 1.0));
    uint32_t transformLoc = glGetUniformLocation(shaderProgram, "uTransform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

static void Unload()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shaderProgram);
    glDeleteTextures(2, textures);
}

int main(int argc, char **argv)
{
    Window window("Test OGL", 1280, 720);
    try 
    {
        window.Init();
    } 
    catch (std::exception e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
        return 1;
    }
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    uint64_t ticks = 0;
    int32_t fps = 0;
    int64_t lastFrame = 0;
    Init();
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
            // std::cout << "FPS: " << fps << std::endl;
            ticks = 0;
            fps = 0;
        }
        window.PollEvents();
        int width = window.GetWidth();
        int height = window.GetHeight();
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        Draw(delta);
        window.SwapBuffers();
    }
    Unload();
    window.Destroy();
    return 0;
}