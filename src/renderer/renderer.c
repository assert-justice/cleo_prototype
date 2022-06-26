#include "renderer.h"
#include "../engine/engine.h"
#include "stdio.h"
#include "../shader_inc.h"
#include "../extern/stb_image/stb_image.h"
#include "../extern/lodepng/lodepng.h"
// #include "../extern/gb_math/gb_math.h"

#define ATLAS_WIDTH 1024

extern Engine engine;

// const float quad[] = {
//     0.5f, 0.5f, 0.0f,       1.0f,1.0f, // top right
//     0.5f, -0.5f, 0.0f,      1.0f,0.0f, // bottom right
//     -0.5f,  0.5f, 0.0f,     0.0f,1.0f, // top left

//     0.5f, -0.5f, 0.0f,      1.0f,0.0f, // bottom right
//     -0.5f,  0.5f, 0.0f,     0.0f,1.0f, // top left
//     -0.5f, -0.5f, 0.0f,     0.0f,0.0f, // bottom left
// };
const float quad[] = {
    1.0f, 1.0f, 0.0f,       1.0f,1.0f, // top right
    1.0f, 0.0f, 0.0f,      1.0f,0.0f, // bottom right
    0.0f,  1.0f, 0.0f,     0.0f,1.0f, // top left

    1.0f, 0.0f, 0.0f,      1.0f,0.0f, // bottom right
    0.0f,  1.0f, 0.0f,     0.0f,1.0f, // top left
    0.0f, 0.0f, 0.0f,     0.0f,0.0f, // bottom left
};
void framebufferCallback(GLFWwindow* window, int width, int height)
{
    window = window;
    glViewport(0, 0, width, height);
    engine.windowStats.width = width;
    engine.windowStats.height = height;
}

void setClearColor(float red, float green, float blue){
    engine.renderer.clearR = red;
    engine.renderer.clearG = green;
    engine.renderer.clearB = blue;
    glClearColor(red, green, blue, 1.0f);
}

void render(){
    mat4x4 proj, view, temp;
    unsigned int projLoc, matLoc, dimLoc;
    // draw sprites
    glBindFramebuffer(GL_FRAMEBUFFER, engine.renderer.renderBuffer);
    glUseProgram(engine.renderer.spriteShader);
    glBindTexture(GL_TEXTURE_2D, engine.renderer.atlasTexture);
    // glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(engine.renderer.VAO);
    mat4x4Orthographic(proj, 0.0f, 
        engine.windowStats.width,
        engine.windowStats.height,
        0.0f, 
        -100.0f, 100.0f);
    projLoc = glGetUniformLocation(engine.renderer.spriteShader, "proj");
    matLoc = glGetUniformLocation(engine.renderer.spriteShader, "matrix");
    dimLoc = glGetUniformLocation(engine.renderer.spriteShader, "dimensions");
    for (int i = 0; i < engine.renderer.numSprites; i++)
    {
        glProgramUniformMatrix4fv(
            engine.renderer.spriteShader, 
            projLoc, 
            1, GL_FALSE, 
            (const GLfloat*)&proj);
        glProgramUniformMatrix4fv(
            engine.renderer.spriteShader, 
            matLoc, 
            1, GL_FALSE, 
            (const GLfloat*)&engine.renderer.sprites[i].matrix);
        glProgramUniform4fv(engine.renderer.spriteShader,
            dimLoc,
            1, (const GLfloat*)&engine.renderer.sprites[i].dimensions      
            );
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    // draw render texture
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    mat4x4Identity(proj);
    // intentionally flipped
    mat4x4Orthographic(proj, 0.0f,
        engine.windowStats.width, 
        0.0f,
        engine.windowStats.height, 
        -100.0f, 100.0f);
    mat4x4Identity(view);
    float ratio = engine.windowStats.height / engine.renderer.height;
    mat4x4Scale(view, vec3New(engine.renderer.width * ratio,
        engine.renderer.height * ratio, 1.0f));
    mat4x4MultiplyMatrix(temp, view, proj);
    glProgramUniformMatrix4fv(
        engine.renderer.shaderProgram, 
        glGetUniformLocation(engine.renderer.shaderProgram, "proj"), 
        1, GL_FALSE, (const GLfloat*)&temp);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(engine.renderer.shaderProgram);
    glBindTexture(GL_TEXTURE_2D, engine.renderer.renderTexture);
    glBindVertexArray(engine.renderer.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void initRenderer(int rendererWidth, int rendererHeight){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    engine.renderer.width = rendererWidth;
    engine.renderer.height = rendererHeight;
    glfwSetFramebufferSizeCallback(engine.window, framebufferCallback);
    glViewport(0, 0, engine.windowStats.width, engine.windowStats.height);
    // tr, br, tl
    // br, bl, tl
    // init vertex buffers
    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    unsigned int shaderProgram = loadShader(simple_vert_script, simple_frag_script);
    engine.renderer.spriteShader = loadShader(sprite_vert_script, simple_frag_script);
    glUseProgram(shaderProgram);
    unsigned int positionLoc, textureLoc;
    positionLoc = glGetAttribLocation(shaderProgram, "aPos");
    textureLoc = glGetAttribLocation(shaderProgram, "aCoord");
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(positionLoc);
    glVertexAttribPointer(textureLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(textureLoc);
    engine.renderer.VAO = VAO;
    engine.renderer.shaderProgram = shaderProgram;
    // create atlas texture
    unsigned int atlasBuffer;
    glGenFramebuffers(1, &atlasBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, atlasBuffer);
    unsigned int atlasTexture;
    glGenTextures(1, &atlasTexture);
    glBindTexture(GL_TEXTURE_2D, atlasTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ATLAS_WIDTH, ATLAS_WIDTH, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, atlasTexture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    engine.renderer.atlasTexture = atlasTexture;
    engine.renderer.atlasBuffer = atlasBuffer;
    // create render texture
    unsigned int renderBuffer;
    glGenFramebuffers(1, &renderBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, renderBuffer);
    unsigned int renderTexture;
    glGenTextures(1, &renderTexture);
    glBindTexture(GL_TEXTURE_2D, renderTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, engine.renderer.width, engine.renderer.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(engine.renderer.clearR, engine.renderer.clearG, engine.renderer.clearB, 1.0f);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    engine.renderer.renderTexture = renderTexture;
    engine.renderer.renderBuffer = renderBuffer;

    engine.renderer.numSprites = 2;
    mat4x4Identity(engine.renderer.sprites[0].matrix);
    mat4x4Scale(engine.renderer.sprites[0].matrix, vec3New(24.0f, 24.0f, 0.0f));
    float cell = 24.0f / ATLAS_WIDTH;
    engine.renderer.sprites[0].dimensions = vec4New(0, cell, cell, cell);

    mat4x4Identity(engine.renderer.sprites[1].matrix);
    mat4x4Scale(engine.renderer.sprites[1].matrix, vec3New(24.0f, 24.0f, 0.0f));
    mat4x4Translate(engine.renderer.sprites[1].matrix, vec3New(24.0f, 0.0f, 0.0f));
    engine.renderer.sprites[1].dimensions = vec4New(cell, cell, cell, cell);
    blitFileToAtlas("game_data/sprites/characters_packed.png",0,0);
}

void freeRenderer(){
    glDeleteProgram(engine.renderer.shaderProgram);
    glDeleteFramebuffers(1, &engine.renderer.atlasBuffer);
    glDeleteTextures(1, &engine.renderer.atlasTexture);
}

void blitFileToAtlas(const char* fname, int xOffset, int yOffset){
    glBindFramebuffer(GL_FRAMEBUFFER, engine.renderer.atlasBuffer);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, numChannels;
    // stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(fname, &width, &height, &numChannels, 0);
    if(data){
        // printf("%i %i %i %i\n", data[0], data[1], data[2], data[3]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("file %s failed to load\n", fname);
    }
    stbi_image_free(data);
    mat4x4 proj, view, temp;
    mat4x4Orthographic(proj, 0.0f, 
        engine.windowStats.width, 
        engine.windowStats.height, 
        0.0f, 
        -100.0f, 100.0f);
    mat4x4Identity(view);
    mat4x4Scale(view, vec3New(width, height, 1.0f));
    mat4x4Translate(view, vec3New(xOffset, yOffset, 0.0));
    mat4x4MultiplyMatrix(temp, view, proj);
    glProgramUniformMatrix4fv(
        engine.renderer.shaderProgram, 
        glGetUniformLocation(engine.renderer.shaderProgram, "proj"), 
        1, GL_FALSE, (const GLfloat*)&temp);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(engine.renderer.clearR, engine.renderer.clearG, engine.renderer.clearB, 1.0f);
    glUseProgram(engine.renderer.shaderProgram);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(engine.renderer.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDeleteTextures(1, &texture);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int loadShader(const char* vertexShaderSrc, const char* fragmentShaderSrc){
    int  success;
    char infoLog[512];
    unsigned int vertexShader, fragmentShader, shaderProgram;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //const char* vertexShaderSource = (const char*) simple_vert_script; // stupid type conversion
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Shader compilation failed\n%s\n", infoLog);
    }
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //const char* fragmentShaderSource = (const char*) simple_frag_script;
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Shader compilation failed\n%s\n", infoLog);
        glDeleteShader(vertexShader);
    }
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Shader linking failed\n%s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}