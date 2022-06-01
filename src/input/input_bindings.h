#ifndef INPUT_BINDINGS
#define INPUT_BINDINGS
#include "wren/wren.h"
void getKeyHook(WrenVM* vm);
WrenForeignMethodFn bindInput(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature);
#endif
