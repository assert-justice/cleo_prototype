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

    result = ma_sound_init_from_file(&engine.audioSystem.engine, "game_data/sfx/Climb_Rope_Loop_00.wav", 0, NULL, NULL, &engine.audioSystem.sounds[0]);
    if (result != MA_SUCCESS) {
        printf("Failed to load sound/n");
        return 0;
    }

    // ma_sound_set_min_gain(&engine.audioSystem.sounds[0], 100.0f);
    ma_sound_start(&engine.audioSystem.sounds[0]);
    // ma_engine_play_sound(&engine.audioSystem.engine, "game_data/sfx/Climb_Rope_Loop_00.wav", NULL);
    return 1;
}
void freeAudioSystem(){
    ma_sound_uninit(&engine.audioSystem.sounds[0]);
    ma_engine_uninit(&engine.audioSystem.engine);
}
