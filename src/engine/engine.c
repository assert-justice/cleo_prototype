#include "engine.h"
#include "stdio.h"
#include "string.h"
#include "sys/time.h"
// #include "../wren_inc.h"
#include "../file_io/file_io.h"
#include "../window/window.h"
#include "../audio_system/audio_system.h"

Engine engine = {0};

int initEngine(const char* srcPath){
    // Get the source of our main.wren file.
    if(!fileExists(srcPath)){
        printf("No file found at path '%s'\n", srcPath);
        return 0;
    }
    // Find last '/' in srcPath. The substring up to that point is the root path for filesystem calls.
    int idx = 0;
    for (size_t i = 0; i < strlen(srcPath); i++)
    {
        if(srcPath[i] == '/'){
            idx = (int)i;
        }
    }
    strncpy(engine.path, srcPath, idx);
    // Read src file
    const char* src = readFile(srcPath);
    
    // init audio system
    initAudioSystem();
    // init vm
    engine.vm = wrenHelpInit();
    // make call handles for engine methods
    engine.updateHandle = wrenMakeCallHandle(engine.vm, "update(_)");
    WrenHandle* initHandle = wrenMakeCallHandle(engine.vm, "init()");
    // actually execute the script. Otherwise we crash
    wrenInterpret(engine.vm, "main", src);
    // get the handle for the main class
    wrenEnsureSlots(engine.vm, 1);
    wrenGetVariable(engine.vm, "main", "Main", 0);
    engine.classHandle = wrenGetSlotHandle(engine.vm, 0);
    // call init on engine class
    wrenCall(engine.vm, initHandle);
    // we no longer need the init handle
    wrenReleaseHandle(engine.vm, initHandle);
    // initRoot(rootSrc);
    gameLoop();
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
    freeRenderer();
    freeWindow();
    wrenReleaseHandle(engine.vm, engine.classHandle);
    wrenReleaseHandle(engine.vm, engine.updateHandle);
    freeAudioSystem();
    if(engine.shouldLog) fclose(engine.logFile);
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