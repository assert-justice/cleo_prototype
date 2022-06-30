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

void setGainAudioSourceHook(WrenVM* vm){
    wrenEnsureSlots(vm, 3);
    int idx = (int)wrenGetSlotDouble(vm, 1);
    float gain = (float)wrenGetSlotDouble(vm, 2);
    setGainAudioSource(idx, gain);
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
      else if(strcmp(signature, "setGainAudioSource(_,_)") == 0 && isStatic){
        return setGainAudioSourceHook;
      }
    }
  }
  return NULL;
}