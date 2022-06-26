#include "renderer_bindings.h"
#include "renderer.h"
#include "string.h"

void initRendererHook(WrenVM* vm){
  wrenEnsureSlots(vm, 4);
  wrenSetSlotString(vm, 2, "width");
  wrenGetMapValue(vm, 1, 2, 3);
  int width = (int)wrenGetSlotDouble(vm, 3);
  wrenSetSlotString(vm, 2, "height");
  wrenGetMapValue(vm, 1, 2, 3);
  int height = (int)wrenGetSlotDouble(vm, 3);
  initRenderer(width, height);
}

void setClearColorHook(WrenVM* vm){
    wrenEnsureSlots(vm, 4);
    float red = (float) wrenGetSlotDouble(vm, 1);
    float green = (float) wrenGetSlotDouble(vm, 2);
    float blue = (float) wrenGetSlotDouble(vm, 3);
    setClearColor(red, green, blue);
}

void addSpriteHook(WrenVM* vm){
  wrenEnsureSlots(vm, 1);
  int val = addSprite();
  wrenSetSlotDouble(vm, 0, (double)val);
}

WrenForeignMethodFn bindRenderer(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature)
{
  if (strcmp(module, "renderer") == 0){
    if (strcmp(className, "Renderer") == 0){
      if(strcmp(signature, "privateInit(_)") == 0 && isStatic){
        return initRendererHook;
      }
      else if(strcmp(signature, "setClearColor(_,_,_)") == 0 && isStatic){
        return setClearColorHook;
      }
      else if(strcmp(signature, "addSprite()") == 0 && isStatic){
        return addSpriteHook;
      }
    }
  }
  return NULL;
}