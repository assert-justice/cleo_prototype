#ifndef AUDIO
#define AUDIO
#include "../extern/miniaudio/miniaudio.h"

typedef struct AudioSystem
{
    ma_engine engine;
} AudioSystem;

int initAudioSystem();
void freeAudioSystem();
#endif
