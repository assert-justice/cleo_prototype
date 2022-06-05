#include "renderer.h"
#include "../engine/engine.h"
#include "stdio.h"

extern Engine engine;

void framebufferCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void setClearColor(float red, float green, float blue){
    glClearColor(red, green, blue, 1.0f);
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT);
}

void initRenderer(){
    glfwSetFramebufferSizeCallback(engine.window, framebufferCallback);
    glViewport(0, 0, engine.windowStats.width, engine.windowStats.width);
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}