#include "window.h"
#include <stdio.h>

extern Engine engine;

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

// glfwSetErrorCallback(error_callback);
    // if(!glfwInit()){
    //     printf("glfw failed to init");
    // }
    // GLFWwindow* window = glfwCreateWindow(640, 480, "Cleo", NULL, NULL);
    // glfwMakeContextCurrent(window);
    // glfwSetKeyCallback(window, key_callback);
    // gladLoadGLES2(glfwGetProcAddress);
    // while (!glfwWindowShouldClose(window))
    // {
    //     // Keep running
    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    // }
    // glfwDestroyWindow(window);
    // glfwTerminate();

int initWindow(){
    if(!glfwInit()){
        printf("glfw failed to init");
        return 0;
    }
    glfwSetErrorCallback(error_callback);
    GLFWwindow* window = glfwCreateWindow(engine.windowWidth, engine.windowHeight, engine.name, NULL, NULL);
    engine.window = window;
    glfwMakeContextCurrent(window);
    gladLoadGLES2(glfwGetProcAddress);
    return 1;
}

void freeWindow(){
    glfwDestroyWindow(engine.window);
    glfwTerminate();
}