#ifndef ENGINE
#define ENGINE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../extern/glad/gles2.h"
#include "GLFW/glfw3.h"
#include "../wren_help/wren_help.h"
#include "../input/input.h"
#include "../window/window.h"
#include "../renderer/renderer.h"
#include "../audio_system/audio_system.h"

typedef struct {
    GLFWwindow* window;
    WrenVM* vm;
    WrenHandle* classHandle;
    WrenHandle* updateHandle;
    WindowStats windowStats;
    Renderer renderer;
    AudioSystem audioSystem;
    FILE* logFile;
    int shouldLog;
    char path[256];
} Engine;

// Initialize the engine. 
//
// Starts wren vm, reads settings, and launches subsystems.
int initEngine(const char* srcPath);
void quitEngine();
void gameLoop();
int enableLogging(const char* fname);
#endif