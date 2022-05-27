#ifndef FILE_IO
#define FILE_IO
char* readFile(const char* path);
int fileExists(const char * path);
// void readFileHook(WrenVM* vm);
// void fileExistsHook(WrenVM* vm);
int writeFile(const char* path, const char* text);
// void writeFileHook(WrenVM* vm);
#endif
