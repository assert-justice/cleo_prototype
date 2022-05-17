#include "wren/wren.h"

// Helper functions relevant to wren instances.

static void writeFn(WrenVM* vm, const char* text);

void errorFn(WrenVM* vm, WrenErrorType errorType,
             const char* module, const int line,
             const char* msg);

WrenVM* wrenInit();