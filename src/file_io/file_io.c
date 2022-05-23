#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wren/wren.h"

#include "file_io.h"

char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 1);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  buffer[bytesRead] = '\0';

  fclose(file);
  // printf("file len: %i", strlen(buffer));
  return buffer;
}

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

int fileExists(const char * path){
  FILE* file = fopen(path, "rb");
  fclose(file);
  return file ? 1 : 0;
}

void fileExistsHook(WrenVM* vm){
  const char* fname = wrenGetSlotString(vm, 1);
  wrenSetSlotBool(vm, 0, fileExists(fname));
}

int writeFile(const char* path, const char* text){
  FILE* file = fopen(path, "wb");
  fprintf(file, text);
  fclose(file);
  return 1;
}

void writeFileHook(WrenVM* vm){
  const char* fname = wrenGetSlotString(vm, 1);
  const char* text = wrenGetSlotString(vm, 2);
  writeFile(fname, text);
}