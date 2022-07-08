#include "audio_system.h"
#include "stdio.h"
#include "../engine/engine.h"
#define MAX_SOUNDS 16

extern Engine engine;

int initAudioSystem(){
    engine.audioSystem.sounds = (ma_sound*)calloc(MAX_SOUNDS, sizeof(ma_sound));
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
    int res = idx >= 0 && idx < engine.audioSystem.numSounds;
    if(!res) printf("Warning: %i is not a valid audio source index.", idx);
    return res;
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
    result = ma_sound_init_from_file(&engine.audioSystem.engine, fname, MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_STREAM, NULL, NULL, &engine.audioSystem.sounds[idx]);
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

int audioSourceIsPlaying(int idx){
    if(!validIdx(idx)) return 0;
    return (int)ma_sound_is_playing(&engine.audioSystem.sounds[idx]);
}

void setVolumeAudioSource(int idx, double volume){
    if(!validIdx(idx)) return;
    ma_sound_set_volume(&engine.audioSystem.sounds[idx], (float)volume);
}

double getVolumeAudioSource(int idx){
    if(!validIdx(idx)) return 0.0;
    return (double)ma_sound_get_volume(&engine.audioSystem.sounds[idx]);
}

void loopAudioSource(int idx, int shouldLoop){
    if(!validIdx(idx)) return;
    ma_sound_set_looping(&engine.audioSystem.sounds[idx], (ma_bool32) shouldLoop);
}
int audioSourceIsLooping(int idx){
    if(!validIdx(idx)) return 0;
    return (int)ma_sound_is_looping(&engine.audioSystem.sounds[idx]);
}