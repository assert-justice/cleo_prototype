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
    // 
    // ma_sound sound;

    // result = ma_sound_init_from_file(&engine.audioSystem.engine, "game_data/sfx/Climb_Rope_Loop_00.wav", 0, NULL, NULL, &engine.audioSystem.sounds[0]);
    // if (result != MA_SUCCESS) {
    //     printf("Failed to load sound/n");
    //     return 0;
    // }
    // ma_sound_start(&engine.audioSystem.sounds[0]);
    return 1;
}
void freeAudioSystem(){
    for (int i = 0; i < engine.audioSystem.numSounds; i++){
        ma_sound_uninit(&engine.audioSystem.sounds[i]);
    }
    
    ma_engine_uninit(&engine.audioSystem.engine);
}

int validIdx(int idx){
    return idx >= 0 && idx < engine.audioSystem.numSounds;
}

int addAudioSource(){
    int val = -1;
    if (engine.audioSystem.numSounds < MAX_SOUNDS){
        val = engine.audioSystem.numSounds;
        engine.audioSystem.numSounds++;
    }
    return val;
}

int getNumAudioSources(){
    return engine.audioSystem.numSounds;
}

int getMaxAudioSources(){
    return MAX_SOUNDS;
}

int loadAudioSource(int idx, const char* fname){
    if(!validIdx(idx)) return 0;
    ma_result result;
    result = ma_sound_init_from_file(&engine.audioSystem.engine, fname, 0, NULL, NULL, &engine.audioSystem.sounds[idx]);
    if (result != MA_SUCCESS) {
        printf("Failed to load sound %s/n", fname);
        return 0;
    }
    return 1;
}

void playAudioSource(int idx){
    if(!validIdx(idx)) return;
    ma_sound_start(&engine.audioSystem.sounds[idx]);
}

void pauseAudioSource(int idx){
    if(!validIdx(idx)) return;
    ma_sound_stop(&engine.audioSystem.sounds[idx]);
}

void stopAudioSource(int idx){
    if(!validIdx(idx)) return;
    ma_sound_stop(&engine.audioSystem.sounds[idx]);
    ma_sound_seek_to_pcm_frame(&engine.audioSystem.sounds[idx], 0);
}