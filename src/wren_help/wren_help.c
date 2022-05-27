#ifndef WREN_HELP
#include "wren_help.h"
#include "stdio.h"
#include "string.h"
#include "../wren_inc.h"
#include "../file_io/file_io_bindings.h"

void writeFn(WrenVM* vm, const char* text)
{
  printf("%s", text);
}

void errorFn(WrenVM* vm, WrenErrorType errorType,
             const char* module, const int line,
             const char* msg)
{
  switch (errorType)
  {
    case WREN_ERROR_COMPILE:
    {
      printf("[%s line %d] [Error] %s\n", module, line, msg);
    } break;
    case WREN_ERROR_STACK_TRACE:
    {
      printf("[%s line %d] in %s\n", module, line, msg);
    } break;
    case WREN_ERROR_RUNTIME:
    {
      printf("[Runtime Error] %s\n", msg);
    } break;
  }
}

WrenLoadModuleResult moduleLoader(WrenVM* vm, const char* name)
{
  WrenLoadModuleResult result = {0};
  if (strcmp(name, "json") == 0)
  {
    result.source = json;
  }
  else if (strcmp(name, "fs") == 0)
  {
    result.source = file_system;
  }
  else
  {
    result.source = NULL;
  }
  return result;
}

WrenForeignMethodFn bindForeignMethod(WrenVM* vm,
  const char* module,
  const char* className,
  bool isStatic,
  const char* signature)
{
  WrenForeignMethodFn method;
  if (method = bindFileIO(module, className, isStatic, signature)) return method;
  printf("Bind attempt failed\nmodule: '%s' match: %i\nclassName: '%s' match: %i\nsignature: '%s' match: %i\n", 
    module, strcmp(module, "fs"), className, strcmp(className, "FileSystem"), signature, strcmp(signature, "read(_)"));
  return NULL;
}

WrenVM* wrenHelpInit()
{
  WrenConfiguration config;
  wrenInitConfiguration(&config);
  config.writeFn = &writeFn;
  config.errorFn = &errorFn;
  config.loadModuleFn = &moduleLoader;
  config.bindForeignMethodFn = &bindForeignMethod;
  WrenVM* vm = wrenNewVM(&config);
  return vm;
}
#endif