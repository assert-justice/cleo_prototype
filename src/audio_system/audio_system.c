#include "audio_system.h"
#include "stdio.h"
#include "../engine/engine.h"

extern Engine engine;

int initAudioSystem(){
    ma_result result;
    result = ma_engine_init(NULL, &engine.audioSystem.engine);
    if (result != MA_SUCCESS) {
        printf("Failed to init audio system.\n");
        return 0;  // Failed to initialize the engine.
    }
    return 1;
}
void freeAudioSystem(){
    ma_engine_uninit(&engine.audioSystem.engine);
}
