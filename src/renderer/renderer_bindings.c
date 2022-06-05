#include "renderer_bindings.h"
#include "renderer.h"
#include "string.h"

void initRendererHook(WrenVM* vm){
    initRenderer();
}

void setClearColorHook(WrenVM* vm){
    wrenEnsureSlots(vm, 4);
    float red = (float) wrenGetSlotDouble(vm, 1);
    float green = (float) wrenGetSlotDouble(vm, 2);
    float blue = (float) wrenGetSlotDouble(vm, 3);
    setClearColor(red, green, blue);
}

WrenForeignMethodFn bindRenderer(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature)
{
  if (strcmp(module, "renderer") == 0){
    if (strcmp(className, "Renderer") == 0){
      if(strcmp(signature, "privateInit()") == 0 && isStatic){
        return initRendererHook;
      }
      else if(strcmp(signature, "setClearColor(_,_,_)") == 0 && isStatic){
        return setClearColorHook;
      }
    }
  }
  return NULL;
}