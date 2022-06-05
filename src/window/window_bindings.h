#ifndef WINDOW_BINDINGS
#define WINDOW_BINDINGS
#include "wren/wren.h"
#include "window.h"

WrenForeignMethodFn bindWindow(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature);
#endif
