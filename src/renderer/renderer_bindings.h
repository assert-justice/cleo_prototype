#ifndef RENDERER_BINDINGS
#define RENDERER_BINDINGS
#include "wren/wren.h"
WrenForeignMethodFn bindRenderer(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature);
#endif
