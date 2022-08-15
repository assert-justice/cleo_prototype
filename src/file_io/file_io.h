#ifndef FILE_IO
#define FILE_IO
char* readFile(const char* path);
int fileExists(const char* path);
int writeFile(const char* path, const char* text);
#endif
