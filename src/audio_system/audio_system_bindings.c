#include "audio_system_bindings.h"
#include "stdio.h"
#include "string.h"
#include "audio_system.h"

void addAudioSourceHook(WrenVM* vm){
    wrenEnsureSlots(vm, 1);
    int val = addAudioSource();
    wrenSetSlotDouble(vm, 0, (double)val);
}

void getNumAudioSourcesHook(WrenVM* vm ){
    int val = getNumAudioSources();
    wrenEnsureSlots(vm, 1);
    wrenSetSlotDouble(vm, 0, (double)val);
}
void getMaxAudioSourcesHook(WrenVM* vm ){
    int val = getMaxAudioSources();
    wrenEnsureSlots(vm, 1);
    wrenSetSlotDouble(vm, 0, (double)val);
}
void loadAudioSourceHook(WrenVM* vm){
    wrenEnsureSlots(vm, 3);
    int idx = (int)wrenGetSlotDouble(vm, 1);
    const char* fname = wrenGetSlotString(vm, 2);
    bool res = (bool)loadAudioSource(idx, fname);
    wrenSetSlotBool(vm, 0, res);
}
void playAudioSourceHook(WrenVM* vm){
    wrenEnsureSlots(vm, 2);
    int idx = (int)wrenGetSlotDouble(vm, 1);
    playAudioSource(idx);
}
void pauseAudioSourceHook(WrenVM* vm){
    wrenEnsureSlots(vm, 2);
    int idx = (int)wrenGetSlotDouble(vm, 1);
    pauseAudioSource(idx);
}
void stopAudioSourceHook(WrenVM* vm){
    wrenEnsureSlots(vm, 2);
    int idx = (int)wrenGetSlotDouble(vm, 1);
    stopAudioSource(idx);
}
void audioSourceIsPlayingHook(WrenVM* vm){
  wrenEnsureSlots(vm, 2);
  int idx = (int)wrenGetSlotDouble(vm, 1);
  int val = audioSourceIsPlaying(idx);
  wrenSetSlotDouble(vm, 0, (double)val);
}
void getVolumeAudioSourceHook(WrenVM* vm){
  wrenEnsureSlots(vm, 2);
  int idx = (int)wrenGetSlotDouble(vm, 1);
  wrenSetSlotDouble(vm, 0, getVolumeAudioSource(idx));
}
void setVolumeAudioSourceHook(WrenVM* vm){
    wrenEnsureSlots(vm, 3);
    int idx = (int)wrenGetSlotDouble(vm, 1);
    setVolumeAudioSource(idx, wrenGetSlotDouble(vm, 2));
}
void loopAudioSourceHook(WrenVM* vm){
  wrenEnsureSlots(vm, 3);
  int idx = (int)wrenGetSlotDouble(vm, 1);
  loopAudioSource(idx, (int)wrenGetSlotBool(vm, 2));
}
void audioSourceIsLoopingHook(WrenVM* vm){
  wrenEnsureSlots(vm, 2);
  int idx = (int)wrenGetSlotDouble(vm, 1);
  wrenSetSlotBool(vm, 0, (bool)audioSourceIsLooping(idx));
}

WrenForeignMethodFn bindAudioSystem(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature)
{
  if (strcmp(module, "audio_system") == 0){
    if (strcmp(className, "AudioSystem") == 0){
      if(strcmp(signature, "addAudioSource()") == 0 && isStatic){
        return addAudioSourceHook;
      }
      else if(strcmp(signature, "getNumAudioSources()") == 0 && isStatic){
        return getNumAudioSourcesHook;
      }
      else if(strcmp(signature, "getMaxAudioSources()") == 0 && isStatic){
        return getMaxAudioSourcesHook;
      }
      else if(strcmp(signature, "loadAudioSource(_,_)") == 0 && isStatic){
        return loadAudioSourceHook;
      }
      else if(strcmp(signature, "playAudioSource(_)") == 0 && isStatic){
        return playAudioSourceHook;
      }
      else if(strcmp(signature, "pauseAudioSource(_)") == 0 && isStatic){
        return pauseAudioSourceHook;
      }
      else if(strcmp(signature, "stopAudioSource(_)") == 0 && isStatic){
        return stopAudioSourceHook;
      }
      else if(strcmp(signature, "audioSourceIsPlaying(_)") == 0 && isStatic){
        return audioSourceIsPlayingHook;
      }
      else if(strcmp(signature, "getVolumeAudioSource(_)") == 0 && isStatic){
        return getVolumeAudioSourceHook;
      }
      else if(strcmp(signature, "setVolumeAudioSource(_,_)") == 0 && isStatic){
        return setVolumeAudioSourceHook;
      }
      else if(strcmp(signature, "loopAudioSource(_,_)") == 0 && isStatic){
        return loopAudioSourceHook;
      }
      else if(strcmp(signature, "audioSourceIsLooping(_)") == 0 && isStatic){
        return audioSourceIsLoopingHook;
      }
    }
  }
  return NULL;
}