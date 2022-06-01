#include "input_bindings.h"
#include "input.h"
#include "../engine/engine.h"
#include "string.h"

extern Engine engine;

// void pollInputsHook(WrenVM* vm){
//     if (engine.input.needsRefresh){
//         // call the refresh inputs handle
//         engine.input.needsRefresh = false;
//     }
//     pollInputs();
// }

void getKeyHook(WrenVM* vm){
    wrenEnsureSlots(vm, 2);
    int code = (int)wrenGetSlotDouble(vm, 1);
    bool state = glfwGetKey(engine.window, code);
    wrenSetSlotBool(vm, 0, state);
}

WrenForeignMethodFn bindInput(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature)
{
  if (strcmp(module, "input") == 0){
    if (strcmp(className, "Input") == 0){
      if(strcmp(signature, "getKey(_)") == 0 && isStatic){
        return getKeyHook;
      }
    //   else if(strcmp(signature, "getMouseButton(_)") == 0 && isStatic){
    //     return getMouseButtonHook;
    //   }
    }
  }
  return NULL;
}