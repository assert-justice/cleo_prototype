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

int addAudioSource();
int getNumAudioSources();
int getMaxAudioSources();
int loadAudioSource(int idx, const char* fname);
void playAudioSource(int idx);
void pauseAudioSource(int idx);
void stopAudioSource(int idx);
#endif
