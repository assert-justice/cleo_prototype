#include "window.h"
#include <stdio.h>
#include "../engine/engine.h"

extern Engine engine;

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWmonitor* getMonitor(int monitorIndex){
    int monitorCount;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
    if (monitorIndex < 0 || monitorIndex >= monitorCount){
        return glfwGetPrimaryMonitor();
    }
    return monitors[monitorIndex];
}

void setWindowStats(WindowStats stats){
    engine.windowStats = stats;
    GLFWmonitor* monitor = getMonitor(stats.monitorIndex);
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!stats.fullScreen){ // if we want a window
        monitor = NULL;
    }
    if(engine.window == NULL){
        engine.window = glfwCreateWindow(stats.width, stats.height, stats.title, monitor, NULL);
    }
    else{
        int xOffset = 0;
        int yOffset = 0;
        if(monitor == NULL){
            xOffset = 100; yOffset = 100;
        }
        glfwSetWindowMonitor(engine.window, monitor, xOffset, yOffset, stats.width, stats.height, stats.refreshRate);
    }
}

WindowStats getWindowStats(){
    return engine.windowStats;
}

int initWindow(WindowStats stats){
    if(!glfwInit()){
        printf("glfw failed to init");
        return 0;
    }
    glfwSetErrorCallback(error_callback);
    setWindowStats(stats);
    glfwMakeContextCurrent(engine.window);
    gladLoadGLES2(glfwGetProcAddress);
    glfwSwapInterval(stats.vsync);
    return 1;
}

void freeWindow(){
    glfwDestroyWindow(engine.window);
    glfwTerminate();
}