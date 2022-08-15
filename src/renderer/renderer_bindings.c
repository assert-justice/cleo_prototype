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
void getNumSpritesHook(WrenVM* vm){
  wrenEnsureSlots(vm, 1);
  int val = getNumSprites();
  wrenSetSlotDouble(vm, 0, (double)val);
}
void getMaxSpritesHook(WrenVM* vm){
  wrenEnsureSlots(vm, 1);
  int val = getMaxSprites();
  wrenSetSlotDouble(vm, 0, (double)val);
}
void setSpriteDimensionsHook(WrenVM* vm){
  wrenEnsureSlots(vm, 6);
  int idx = (int)wrenGetSlotDouble(vm, 1);
  double xOffset = wrenGetSlotDouble(vm, 2);
  double yOffset = wrenGetSlotDouble(vm, 3);
  double width = wrenGetSlotDouble(vm, 4);
  double height = wrenGetSlotDouble(vm, 5);
  setSpriteDimensions(idx, xOffset, yOffset, width, height);
}
void setSpriteTransformHook(WrenVM* vm){
  wrenEnsureSlots(vm, 8);
  int idx = (int)wrenGetSlotDouble(vm, 1);
  double xPos = wrenGetSlotDouble(vm, 2);
  double yPos = wrenGetSlotDouble(vm, 3);
  double zPos = wrenGetSlotDouble(vm, 4);
  double xScale = wrenGetSlotDouble(vm, 5);
  double yScale = wrenGetSlotDouble(vm, 6);
  double angle = wrenGetSlotDouble(vm, 7);
  setSpriteTransform(idx, 
    vec3New(xPos, yPos, zPos), 
    vec3New(xScale, yScale, 0.0),
    angle);
}
void blitFileToAtlasHook(WrenVM* vm){
  wrenEnsureSlots(vm, 4);
  const char* fname = wrenGetSlotString(vm, 1);
  double xOffset = wrenGetSlotDouble(vm, 2);
  double yOffset = wrenGetSlotDouble(vm, 3);
  int width, height;
  int res = blitFileToAtlas(fname, xOffset, yOffset, &width, &height);
  if(!res){
    wrenSetSlotNull(vm, 0);
    return;
  }
  wrenSetSlotNewMap(vm, 0);
  wrenSetSlotString(vm, 1, "width");
  wrenSetSlotDouble(vm, 2, (double)width);
  wrenSetMapValue(vm, 0, 1, 2);
  wrenSetSlotString(vm, 1, "height");
  wrenSetSlotDouble(vm, 2, (double)height);
  wrenSetMapValue(vm, 0, 1, 2);
}
void blitSpriteToAtlasHook(WrenVM* vm){
  wrenEnsureSlots(vm, 2);
  int idx = (int)wrenGetSlotDouble(vm, 1);
  blitSpriteToAtlas(idx);
}
WrenForeignMethodFn bindRenderer(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature)
{
  if (strcmp(module, "engine") == 0){
    if (strcmp(className, "Renderer") == 0){
      if(strcmp(signature, "init(_)") == 0 && isStatic){
        return initRendererHook;
      }
      else if(strcmp(signature, "setClearColor(_,_,_)") == 0 && isStatic){
        return setClearColorHook;
      }
      else if(strcmp(signature, "addSprite()") == 0 && isStatic){
        return addSpriteHook;
      }
      else if(strcmp(signature, "getNumSprites()") == 0 && isStatic){
        return getNumSpritesHook;
      }
      else if(strcmp(signature, "getMaxSprites()") == 0 && isStatic){
        return getMaxSpritesHook;
      }
      else if(strcmp(signature, "setSpriteDimensions(_,_,_,_,_)") == 0 && isStatic){
        return setSpriteDimensionsHook;
      }
      else if(strcmp(signature, "setSpriteTransform(_,_,_,_,_,_,_)") == 0 && isStatic){
        return setSpriteTransformHook;
      }
      else if(strcmp(signature, "blitFileToAtlas(_,_,_)") == 0 && isStatic){
        return blitFileToAtlasHook;
      }
      else if(strcmp(signature, "blitSpriteToAtlas(_)") == 0 && isStatic){
        return blitSpriteToAtlasHook;
      }
    }
  }
  return NULL;
}