#ifndef RENDERER
#define RENDERER
#include "../extern/glad/gles2.h"
#include "GLFW/glfw3.h"

typedef struct {
    int width;
    int height;
    int pixelMode;
} Renderer;

void initRenderer();
void render();
void setClearColor(float red, float green, float blue);

#endif
