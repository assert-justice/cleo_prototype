#include "engine_bindings.h"
#include "engine.h"

extern Engine engine;

void engineInitHook(WrenVM* vm){
    // wrenGetMapValue()
    wrenEnsureSlots(vm, 4);
    // slot 0: return val, slot 1: map, slot 2: key, slot 3: value
    wrenSetSlotString(vm, 2, "name");
    wrenGetMapValue(vm, 1, 2, 3);
    engine.name = wrenGetSlotString(vm, 3);
}

WrenForeignMethodFn bindEngine(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature)
{
  if (strcmp(module, "engine") == 0){
    if (strcmp(className, "Engine") == 0){
      if(strcmp(signature, "privateInit(_)") == 0 && isStatic){
        return engineInitHook;
      }
    }
  }
  return NULL;
}