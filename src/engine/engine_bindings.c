#include "engine_bindings.h"
#include "engine.h"
#include "string.h"

extern Engine engine;

void quitHook(WrenVM* vm){
  wrenEnsureSlots(vm, 0);
  quitEngine();
}

// void initRootHook(WrenVM* vm){
//   const char* src = wrenGetSlotString(vm, 1);
//   // initRoot(src);
// }

void enableLoggingHook(WrenVM* vm){
  wrenEnsureSlots(vm, 2);
  const char* fname = wrenGetSlotString(vm, 1);
  wrenSetSlotBool(vm, 0, (bool)enableLogging(fname));
}

WrenForeignMethodFn bindEngine(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature)
{
  if (strcmp(module, "engine") == 0){
    if (strcmp(className, "Engine") == 0){
      if(strcmp(signature, "quit()") == 0 && isStatic){
        return quitHook;
      }
      // else if(strcmp(signature, "privateInitRoot(_)") == 0 && isStatic){
      //   return initRootHook;
      // }
      else if(strcmp(signature, "enableLogging(_)") == 0 && isStatic){
        return enableLoggingHook;
      }
    }
  }
  return NULL;
}