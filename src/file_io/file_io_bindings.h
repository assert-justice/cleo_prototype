#ifndef FILE_IO_BINDINGS
#define FILE_IO_BINDINGS
#include "wren/wren.h"
WrenForeignMethodFn bindFileIO(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature);
#endif
