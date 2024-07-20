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

// float vertices[] = {
//     // positions          // colors           // texture coords
//      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//     -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
// };

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
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
static glm::mat4 model;

static glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

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

    int32_t stride = 5 * sizeof(float);
    glEnableVertexAttribArray(0); // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    // glEnableVertexAttribArray(1); // color
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,stride, (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1); //texcoords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));

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

    model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glEnable(GL_DEPTH_TEST);
}

static void Update(const Window& window, float delta)
{
    const float speed = 100.0f;
    if (window.IsKeyDown(SDLK_W))
    {
        cameraPos += speed * cameraFront * delta;
    }
    if (window.IsKeyDown(SDLK_S))
    {
        cameraPos -= speed * cameraFront * delta;
    }
    if (window.IsKeyDown(SDLK_A))
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * delta;
    }
    if (window.IsKeyDown(SDLK_D))
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * delta;
    }
}

static void Draw(float delta)
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

    uint32_t transformLoc = glGetUniformLocation(shaderProgram, "uTransform");
    for (int i = 0; i < 10; i++)
    {
        model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        glm::mat4 mvp = projection * view * model;
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // transform = glm::rotate(transform, glm::radians(delta * 10), glm::vec3(0.0, 0.0, 1.0));
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
        Update(window, delta);
        int width = window.GetWidth();
        int height = window.GetHeight();
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Draw(delta);
        window.SwapBuffers();
    }
    Unload();
    window.Destroy();
    return 0;
}