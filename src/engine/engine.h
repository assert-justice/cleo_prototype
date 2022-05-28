#ifndef ENGINE
#define ENGINE
#include "../extern/glad/gles2.h"
#include "GLFW/glfw3.h"
#include "../wren_help/wren_help.h"

typedef struct {
    GLFWwindow* window;
    WrenVM* vm;
    char* name;
    int mode;
    int monitor;
    int windowWidth;
    int windowHeight;
    int refreshRate;
    int vsync;
    int pixelMode;
    int internalWidth;
    int internalHeight;
} Engine;
#endif

// Initialize the engine. 
//
// Starts wren vm, reads settings, and launches subsystems.
int initEngine();
void gameLoop();