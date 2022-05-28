#ifndef ENGINE_BINDINGS
#define ENGINE_BINDINGS
#include "wren/wren.h"
WrenForeignMethodFn bindEngine(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature);
#endif
