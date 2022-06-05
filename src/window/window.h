#ifndef WINDOW
#define WINDOW
#include "stdbool.h"

typedef struct{
    const char* title;
    int width;
    int height;
    int refreshRate;
    int vsync;
    bool fullScreen;
    int monitorIndex;
} WindowStats;

int initWindow(WindowStats stats);
void setWindowStats(WindowStats stats);
void borderlessFullscreen();
WindowStats getWindowStats();
void freeWindow();

#endif
