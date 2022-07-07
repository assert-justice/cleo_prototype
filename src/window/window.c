#include "window.h"
#include <stdio.h>
#include "../engine/engine.h"

extern Engine engine;

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
    error = error;
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
    GLFWmonitor* monitor = getMonitor(stats.monitorIndex);
    // const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!stats.fullScreen){ // if we want a window
        monitor = NULL;
    }
    else{
        // if it is fullscreen we want to request borderless
        // overwrite the requested stats
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
 
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        stats.width = mode->width;
        stats.height = mode->height;
        stats.refreshRate = mode->refreshRate;
        
        // GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
    }
    engine.windowStats = stats;
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