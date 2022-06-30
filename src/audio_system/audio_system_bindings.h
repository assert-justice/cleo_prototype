#ifndef AUDIO_SYSTEM_BINDINGS
#define AUDIO_SYSTEM_BINDINGS
#include "wren/wren.h"
WrenForeignMethodFn bindAudioSystem(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature);
#endif
