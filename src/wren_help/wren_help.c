#ifndef WREN_HELP
#include "wren_help.h"
#include "stdio.h"
#include "string.h"

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

void moduleLoader(WrenVM* vm, const char* name)
{
  // TODO: 
}

WrenVM* wrenHelpInit()
{
  WrenConfiguration config;
  wrenInitConfiguration(&config);
  config.writeFn = &writeFn;
  config.errorFn = &errorFn;
  WrenVM* vm = wrenNewVM(&config);
  return vm;
}
#endif