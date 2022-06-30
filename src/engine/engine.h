#ifndef ENGINE
#define ENGINE
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
} Engine;

// Initialize the engine. 
//
// Starts wren vm, reads settings, and launches subsystems.
int initEngine();
void quitEngine();
void gameLoop();
void initRoot(const char* rootSrc);
#endif