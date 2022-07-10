#include "engine.h"
#include "../wren_inc.h"
#include "../window/window.h"
#include "../audio_system/audio_system.h"
#include "stdio.h"
#include "sys/time.h"

Engine engine = {0};

int initEngine(){
    // grab logging file
    // engine.shouldLog = 1;
    if(engine.shouldLog) engine.logFile = fopen("logging.txt", "w");
    // init audio system (duh)
    initAudioSystem();
    // init vm
    engine.vm = wrenHelpInit();
    // make call handles for engine methods
    engine.updateHandle = wrenMakeCallHandle(engine.vm, "update(_)");
    WrenHandle* initHandle = wrenMakeCallHandle(engine.vm, "privateInit()");
    // WrenHandle* launchHandle = wrenMakeCallHandle(engine.vm, "launch()");
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
    // initWindow();
    initRoot(rootSrc);
    // gameLoop();
    return 1;
}

int enableLogging(const char* fname){
    engine.shouldLog = true;
    if(engine.logFile) fclose(engine.logFile);
    engine.logFile = fopen(fname, "w");
    if (!engine.logFile){
        engine.shouldLog = false;
        return 0;
    }
    return 1;
}

void quitEngine(){
    glfwSetWindowShouldClose(engine.window, 1);
}

void freeEngine(){
    freeWindow();
    wrenReleaseHandle(engine.vm, engine.classHandle);
    wrenReleaseHandle(engine.vm, engine.updateHandle);
    freeAudioSystem();
    if(engine.shouldLog) fclose(engine.logFile);
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
    WrenHandle* callHandle = wrenMakeCallHandle(engine.vm, "privateReady(_)");
    wrenEnsureSlots(engine.vm, 2);
    // set the engine class to slot 0
    wrenSetSlotHandle(engine.vm, 0, engine.classHandle);
    // set the root node to slot 1
    wrenSetSlotHandle(engine.vm, 1, rootHandle);
    wrenCall(engine.vm, callHandle);
    wrenReleaseHandle(engine.vm, callHandle);    
    gameLoop();
}

double getTime(){
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (double)current_time.tv_sec + (double)current_time.tv_usec / 1000000; 
}

void gameLoop(){
    double t = 0.0;
    double tickRate = 100; // ticks / second
    const double dt = 1.0 / tickRate; 
    double currentTime = getTime();
    double acc = 0.0;
    double scriptTime;
    double elapsedTime;
    while (!glfwWindowShouldClose(engine.window))
    {
        double newTime = getTime();
        double frameTime = newTime - currentTime;
        if(engine.shouldLog) fprintf(engine.logFile, "RENDER start: %lf end: %lf\n", newTime, frameTime);

        currentTime = newTime;
        acc += frameTime;
        while(acc >= dt){
            glfwPollEvents();
            wrenEnsureSlots(engine.vm, 2);
            wrenSetSlotDouble(engine.vm, 1, dt);
            wrenSetSlotHandle(engine.vm, 0, engine.classHandle);
            scriptTime = getTime();
            wrenCall(engine.vm, engine.updateHandle);
            elapsedTime = getTime() - scriptTime;
            if(engine.shouldLog) fprintf(engine.logFile, "SCRIPT start: %lf end: %lf\n", scriptTime, elapsedTime);
            acc -= dt;
            t += dt;
        }
        render();
        glfwSwapBuffers(engine.window);
    }
    freeEngine();
}