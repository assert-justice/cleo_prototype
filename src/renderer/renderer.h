#ifndef RENDERER
#define RENDERER
#include "../extern/glad/gles2.h"
#include "GLFW/glfw3.h"
#include "../extern/cc_vector/ccVector.h"

typedef struct Sprite {
    mat4x4 matrix;
    vec4 dimensions;
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
    vec3 transparentColor;
    Sprite* sprites;
    int numSprites;
} Renderer;

void initRenderer(int rendererWidth, int rendererHeight);
void freeRenderer();
void render();
void setClearColor(float red, float green, float blue);
int blitFileToAtlas(const char* fname, double xOffset, double yOffset, int* width, int* height);
void blitSpriteToAtlas(int idx);
unsigned int loadShader(const char* vertexShaderSrc, const char* fragmentShaderSrc);
int addSprite();
int getNumSprites();
int getMaxSprites();
void setSpriteDimensions(int idx, double xOffset, double yOffset, double width, double height);
void setSpriteTransform(int idx, vec3 position, vec3 scale, double angle);
#endif
