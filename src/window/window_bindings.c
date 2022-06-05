#include "window_bindings.h"
#include "../engine/engine.h"
#include "string.h"
#include "stdio.h"

extern Engine engine;

WindowStats unpackWindowStats(int mapSlot, int keySlot, int valueSlot){
    WindowStats stats = {0};
    // const char* title;
    wrenSetSlotString(engine.vm, keySlot, "title");
    wrenGetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    stats.title = wrenGetSlotString(engine.vm, valueSlot);
    // int width;
    wrenSetSlotString(engine.vm, keySlot, "width");
    wrenGetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    stats.width = (int) wrenGetSlotDouble(engine.vm, valueSlot);
    // int height;
    wrenSetSlotString(engine.vm, keySlot, "height");
    wrenGetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    stats.height = (int) wrenGetSlotDouble(engine.vm, valueSlot);
    // printf("height: %i\n", stats.height);
    // int refreshRate;
    wrenSetSlotString(engine.vm, keySlot, "refreshRate");
    wrenGetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    stats.refreshRate = (int) wrenGetSlotDouble(engine.vm, valueSlot);
    // int vsync;
    wrenSetSlotString(engine.vm, keySlot, "vsync");
    wrenGetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    stats.vsync = (int) wrenGetSlotBool(engine.vm, valueSlot);
    // bool fullScreen;
    wrenSetSlotString(engine.vm, keySlot, "fullScreen");
    wrenGetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    stats.fullScreen = wrenGetSlotBool(engine.vm, valueSlot);
    // int monitorIndex;
    wrenSetSlotString(engine.vm, keySlot, "monitorIndex");
    wrenGetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    stats.monitorIndex = (int) wrenGetSlotDouble(engine.vm, valueSlot);
    return stats;
}

void packWindowStats(int mapSlot, int keySlot, int valueSlot, WindowStats stats){
    // create a map at the given slot
    wrenSetSlotNewMap(engine.vm, mapSlot);
    // const char* title;
    wrenSetSlotString(engine.vm, keySlot, "title");
    wrenSetSlotString(engine.vm, valueSlot, stats.title);
    wrenSetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    // return;
    // int width;
    wrenSetSlotString(engine.vm, keySlot, "width");
    wrenSetSlotDouble(engine.vm, valueSlot, (double) stats.width);
    wrenSetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    // int height;
    wrenSetSlotString(engine.vm, keySlot, "height");
    wrenSetSlotDouble(engine.vm, valueSlot, (double) stats.height);
    wrenSetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    // int refreshRate;
    wrenSetSlotString(engine.vm, keySlot, "refreshRate");
    wrenSetSlotDouble(engine.vm, valueSlot, (double) stats.refreshRate);
    wrenSetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    // int vsync;
    wrenSetSlotString(engine.vm, keySlot, "vsync");
    wrenSetSlotBool(engine.vm, valueSlot, (bool) stats.vsync);
    wrenSetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    // bool fullScreen;
    wrenSetSlotString(engine.vm, keySlot, "fullScreen");
    wrenSetSlotBool(engine.vm, valueSlot, stats.fullScreen);
    wrenSetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
    // int monitorIndex;
    wrenSetSlotString(engine.vm, keySlot, "monitorIndex");
    wrenSetSlotDouble(engine.vm, valueSlot, (double) stats.monitorIndex);
    wrenSetMapValue(engine.vm, mapSlot, keySlot, valueSlot);
}

void windowInitHook(WrenVM* vm){
    // slot 0 has map
    // printf("howdy\n");
    wrenEnsureSlots(engine.vm, 4);
    WindowStats stats = unpackWindowStats(1, 2, 3);
    initWindow(stats);
    // printf("doody\n");
}

void windowGetStatsHook(WrenVM* vm){
    wrenEnsureSlots(vm, 3);
    WindowStats stats = getWindowStats();
    packWindowStats(0, 1, 2, stats);
}

void windowSetStatsHook(WrenVM* vm){
    wrenEnsureSlots(vm, 4);
    WindowStats stats = unpackWindowStats(1, 2, 3);
    setWindowStats(stats);
}

WrenForeignMethodFn bindWindow(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature)
{
  if (strcmp(module, "window") == 0){
    if (strcmp(className, "Window") == 0){
      if(strcmp(signature, "privateInit(_)") == 0 && isStatic){
        return windowInitHook;
      }
      else if(strcmp(signature, "getStats()") == 0 && isStatic){
        return windowGetStatsHook;
      }
      else if(strcmp(signature, "setStats(_)") == 0 && isStatic){
        return windowSetStatsHook;
      }
    }
  }
  return NULL;
}