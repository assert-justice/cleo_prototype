#include "engine.h"
#include "../wren_inc.h"
#include "../window/window.h"
#include "stdio.h"

Engine engine = {0};

int initEngine(){
    // init vm
    engine.vm = wrenHelpInit();
    // make call handles for engine methods
    engine.updateHandle = wrenMakeCallHandle(engine.vm, "update(_)");
    WrenHandle* initHandle = wrenMakeCallHandle(engine.vm, "init()");
    WrenHandle* launchHandle = wrenMakeCallHandle(engine.vm, "launch()");
    // actually execute the script. Otherwise we crash
    wrenInterpret(engine.vm, "engine", engine_script);
    // get the handle for the engine class
    wrenEnsureSlots(engine.vm, 1);
    wrenGetVariable(engine.vm, "engine", "Engine", 0);
    engine.classHandle = wrenGetSlotHandle(engine.vm, 0);
    // call init on engine class
    wrenCall(engine.vm, initHandle);
    // store the source to the root class
    const char* rootSrc = wrenGetSlotString(engine.vm, 0);
    // we no longer need the init handle
    wrenReleaseHandle(engine.vm, initHandle);
    initWindow();
    initRoot(rootSrc);
    gameLoop();
}

void quitEngine(){
    glfwSetWindowShouldClose(engine.window, 1);
}

void freeEngine(){
    freeWindow();
    wrenReleaseHandle(engine.vm, engine.classHandle);
    wrenReleaseHandle(engine.vm, engine.updateHandle);
}

void initRoot(const char* rootSrc){
    // run the code in our root script
    wrenInterpret(engine.vm, "game", rootSrc);
    wrenEnsureSlots(engine.vm, 2);
    WrenHandle* constructorHandle = wrenMakeCallHandle(engine.vm, "new()");
    // set the game class to be at slot 0
    wrenGetVariable(engine.vm, "game", "Game", 0);
    // call new on game class and set the new instance to slot zero
    wrenCall(engine.vm, constructorHandle);
    // save a handle to the root
    WrenHandle* rootHandle = wrenGetSlotHandle(engine.vm, 0);
    wrenReleaseHandle(engine.vm, constructorHandle);
    // get the handle to set the engine's root
    WrenHandle* callHandle = wrenMakeCallHandle(engine.vm, "privateSetRoot(_)");
    wrenEnsureSlots(engine.vm, 2);
    // set the engine class to slot 0
    wrenSetSlotHandle(engine.vm, 0, engine.classHandle);
    // set the root node to slot 1
    wrenSetSlotHandle(engine.vm, 1, rootHandle);
    wrenCall(engine.vm, callHandle);
    wrenReleaseHandle(engine.vm, callHandle);    
}

void gameLoop(){
    while (!glfwWindowShouldClose(engine.window))
    {
        // Keep running
        glfwSwapBuffers(engine.window);
        glfwPollEvents();
    }
    freeEngine();
}