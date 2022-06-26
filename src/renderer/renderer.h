#ifndef RENDERER
#define RENDERER
#include "../extern/glad/gles2.h"
#include "GLFW/glfw3.h"
#include "../extern/cc_vector/ccVector.h"
#define MAX_SPRITES 16

typedef struct Sprite {
    mat4x4 matrix;
    vec4 dimensions;
    // int xOffset;
    // int yOffset;
    // int width;
    // int height;
} Sprite;

typedef struct {
    unsigned int VAO;
    unsigned int shaderProgram;
    unsigned int spriteShader;
    unsigned int atlasTexture;
    unsigned int atlasBuffer;
    unsigned int renderTexture;
    unsigned int renderBuffer;
    int width;
    int height;
    int pixelMode;
    float clearR;
    float clearG;
    float clearB;
    Sprite sprites[MAX_SPRITES];
    int numSprites;
} Renderer;

void initRenderer(int rendererWidth, int rendererHeight);
void freeRenderer();
void render();
void setClearColor(float red, float green, float blue);
void blitFileToAtlas(const char* fname, int xOffset_x, int yOffset);
unsigned int loadShader(const char* vertexShaderSrc, const char* fragmentShaderSrc);

#endif
