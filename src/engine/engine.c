#include "engine.h"
#include "../wren_inc.h"
#include "../window/window.h"

Engine engine = {0};

int initEngine(){
    engine.vm = wrenHelpInit();
    wrenInterpret(engine.vm, "engine", engine_script);
    wrenEnsureSlots(engine.vm, 1);
    WrenHandle* callHandle = wrenMakeCallHandle(engine.vm, "init()");
    wrenGetVariable(engine.vm, "engine", "Engine", 0);
    wrenCall(engine.vm, callHandle);
    wrenReleaseHandle(engine.vm, callHandle);
    initWindow();
    gameLoop();
    freeWindow();
}

void gameLoop(){
    while (!glfwWindowShouldClose(engine.window))
    {
        // Keep running
        glfwSwapBuffers(engine.window);
        glfwPollEvents();
    }
}