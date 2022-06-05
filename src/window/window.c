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

// void borderlessFullscreen()

//void createWindow(int monitorIndex, int windowType, const char * title, int width, int height, int refreshRate){
void setWindowStats(WindowStats stats){
    engine.windowStats = stats;
    GLFWmonitor* monitor = getMonitor(stats.monitorIndex);
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    // engine.title = stats.title;
    // engine.vsync = stats.vsync;
    if (!stats.fullScreen){ // if we want a window
        monitor = NULL;
    }
    // else if(stats.type == 1){ // if we want borderless mode we use the monitor's settings
    //     // in borderless mode we ignore the requested width, height, and refresh rate
    //     stats.width = mode->width;
    //     stats.height = mode->height;
    //     stats.refreshRate = mode->refreshRate;
    //     glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    //     glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    //     glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    //     glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    // }
    if(engine.window == NULL){
        // printf("width: %i height: %i title: %s\n", stats.width, stats.height, stats.title);
        // engine.title = stats.title;
        // engine.window = glfwCreateWindow(800, 600, "cleo", NULL, NULL);
        engine.window = glfwCreateWindow(stats.width, stats.height, stats.title, monitor, NULL);
        //printf("fuck you too %s\n", stats.title);
        // printf(stats.title);
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
    // WindowStats stats = {0};
    // //GLFWmonitor* monitor = getMonitor(stats.monitorIndex);
    // GLFWmonitor* monitor = glfwGetWindowMonitor(engine.window);
    // const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    // stats.width = mode->width;
    // stats.height = mode->height;
    // stats.refreshRate = mode->refreshRate;
    // stats.title = engine.title;
    // stats.fullScreen = false;
    // stats.monitorIndex = -1;
    // // TODO: stor the vsync setting in the engine struct
    // stats.vsync = engine.vsync;
    // if (monitor != NULL){
    //     stats.fullScreen = true;
    //     int count;
    //     GLFWmonitor** monitors = glfwGetMonitors(&count);
    //     for (int i = 0; i < count; i++){
    //         if(monitors[i] == monitor){
    //             stats.monitorIndex = i;
    //             break;
    //         }
    //     }
    // }
    // return stats;
}

int initWindow(WindowStats stats){
    if(!glfwInit()){
        printf("glfw failed to init");
        return 0;
    }
    glfwSetErrorCallback(error_callback);
    // GLFWwindow* window = glfwCreateWindow(engine.windowWidth, engine.windowHeight, engine.name, NULL, NULL);
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