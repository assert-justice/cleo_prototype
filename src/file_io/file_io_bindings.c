#include "file_io_bindings.h"
#include "file_io.h"
#include "string.h"

void readFileHook(WrenVM* vm)
{
  // TODO: add type checking
  const char* fname = wrenGetSlotString(vm, 1);
  if(!fileExists(fname)){
    wrenSetSlotNull(vm, 0);
    return;
  }
  char* text = readFile(fname);
  wrenSetSlotString(vm, 0, text);
  free(text);
}

void fileExistsHook(WrenVM* vm){
  const char* fname = wrenGetSlotString(vm, 1);
  wrenSetSlotBool(vm, 0, fileExists(fname));
}

void writeFileHook(WrenVM* vm){
  const char* fname = wrenGetSlotString(vm, 1);
  const char* text = wrenGetSlotString(vm, 2);
  writeFile(fname, text);
}

WrenForeignMethodFn bindFileIO(
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature)
{
  if (strcmp(module, "engine") == 0){
    if (strcmp(className, "File") == 0){
      if(strcmp(signature, "read(_)") == 0 && isStatic){
        return readFileHook;
      }
      else if(strcmp(signature, "fileExists(_)") == 0 && isStatic){
        return fileExistsHook;
      }
      else if(strcmp(signature, "write(_,_)") == 0 && isStatic){
        return writeFileHook;
      }
    }
  }
  return NULL;
}