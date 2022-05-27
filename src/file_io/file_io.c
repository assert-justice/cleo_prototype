#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int fileExists(const char * path){
  FILE* file = fopen(path, "rb");
  fclose(file);
  return file ? 1 : 0;
}

int writeFile(const char* path, const char* text){
  FILE* file = fopen(path, "wb");
  fprintf(file, text);
  fclose(file);
  return 1;
}
