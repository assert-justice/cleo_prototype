#ifndef AUDIO
#define AUDIO
#include "../extern/miniaudio/miniaudio.h"

#define MAX_SOUNDS 16

typedef struct AudioSystem
{
    ma_engine engine;
    int numSounds;
    ma_sound sounds[MAX_SOUNDS];
} AudioSystem;

int initAudioSystem();
void freeAudioSystem();
#endif
