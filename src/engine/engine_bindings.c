#include "engine_bindings.h"
#include "engine.h"

extern Engine engine;

void mapGetValue(WrenVM* vm, const char* key){
  // slot 0: unused, slot 1: map, slot 2: key, slot 3: value
  wrenSetSlotString(vm, 2, key);
  wrenGetMapValue(vm, 1, 2, 3);
}

void mapSetValue(WrenVM* vm, const char* key){
  // slot 0: map to return, slot 1: key, slot 2: value
  wrenSetSlotString(vm, 1, key);
  wrenSetMapValue(vm, 0, 1, 2);
}

void setSettingsHook(WrenVM* vm){
  wrenEnsureSlots(vm, 4);
  mapGetValue(vm, "name");
  engine.name = wrenGetSlotString(vm, 3);
  mapGetValue(vm, "windowMode");
  engine.windowMode = (int)wrenGetSlotDouble(vm, 3);
  mapGetValue(vm, "monitor");
  engine.monitor = (int)wrenGetSlotDouble(vm, 3);
  mapGetValue(vm, "windowWidth");
  engine.windowWidth = (int)wrenGetSlotDouble(vm, 3);
  mapGetValue(vm, "windowHeight");
  engine.windowHeight = (int)wrenGetSlotDouble(vm, 3);
  mapGetValue(vm, "refreshRate");
  engine.refreshRate = (int)wrenGetSlotDouble(vm, 3);
  mapGetValue(vm, "vsync");
  engine.vsync = wrenGetSlotBool(vm, 3);
  mapGetValue(vm, "pixelMode");
  engine.pixelMode = (int)wrenGetSlotDouble(vm, 3);
  mapGetValue(vm, "internalWidth");
  engine.internalWidth = (int)wrenGetSlotDouble(vm, 3);
  mapGetValue(vm, "internalHeight");
  engine.internalHeight = (int)wrenGetSlotDouble(vm, 3);
}

void getSettingsHook(WrenVM* vm){
  wrenSetSlotNewMap(vm, 0);
  wrenSetSlotString(vm, 2, engine.name);
  mapSetValue(vm, "name");
  wrenSetSlotDouble(vm, 2, (double)engine.windowMode);
  mapSetValue(vm, "windowMode");
  wrenSetSlotDouble(vm, 2, (double)engine.monitor);
  mapSetValue(vm, "monitor");
  wrenSetSlotDouble(vm, 2, (double)engine.windowWidth);
  mapSetValue(vm, "windowWidth");
  wrenSetSlotDouble(vm, 2, (double)engine.windowHeight);
  mapSetValue(vm, "windowHeight");
  wrenSetSlotDouble(vm, 2, (double)engine.refreshRate);
  mapSetValue(vm, "refreshRate");
  wrenSetSlotBool(vm, 2, engine.vsync);
  mapSetValue(vm, "vsync");
  wrenSetSlotDouble(vm, 2, (double)engine.pixelMode);
  mapSetValue(vm, "pixelMode");
  wrenSetSlotDouble(vm, 2, (double)engine.internalWidth);
  mapSetValue(vm, "internalWidth");
  wrenSetSlotDouble(vm, 2, (double)engine.internalHeight);
  mapSetValue(vm, "internalHeight");
}

WrenForeignMethodFn bindEngine(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature)
{
  if (strcmp(module, "engine") == 0){
    if (strcmp(className, "Engine") == 0){
      if(strcmp(signature, "privateSetSettings(_)") == 0 && isStatic){
        return setSettingsHook;
      }
      else if(strcmp(signature, "getSettings()") == 0 && isStatic){
        return getSettingsHook;
      }
    }
  }
  return NULL;
}