#include "renderer.h"
#include "../engine/engine.h"
#include "stdio.h"
#include "../shader_inc.h"
#include "../extern/stb_image/stb_image.h"
#include "../extern/lodepng/lodepng.h"
// #include "../extern/gb_math/gb_math.h"
#include "../extern/cc_vector/ccVector.h"

extern Engine engine;

void framebufferCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void setClearColor(float red, float green, float blue){
    glClearColor(red, green, blue, 1.0f);
}

void render(){
    mat4x4 proj, view;
    mat4x4Identity(proj);
    unsigned int matLoc = glGetUniformLocation(engine.renderer.shaderProgram, "mat");
    glProgramUniformMatrix4fv(engine.renderer.shaderProgram, matLoc, 1, GL_FALSE, (const GLfloat*)&proj);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(engine.renderer.shaderProgram);
    glBindTexture(GL_TEXTURE_2D, engine.renderer.atlasTexture);
    glBindVertexArray(engine.renderer.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void initRenderer(){
    glfwSetFramebufferSizeCallback(engine.window, framebufferCallback);
    glViewport(0, 0, engine.windowStats.width, engine.windowStats.height);
    float vertices[] = {
        0.5f, 0.5f, 0.0f,       1.0f,1.0f, // top right
        0.5f, -0.5f, 0.0f,      1.0f,0.0f, // bottom right
        -0.5f,  0.5f, 0.0f,     0.0f,1.0f, // top left

        0.5f, -0.5f, 0.0f,      1.0f,0.0f, // bottom right
        -0.5f,  0.5f, 0.0f,     0.0f,1.0f, // top left
        -0.5f, -0.5f, 0.0f,     0.0f,0.0f, // bottom left
    };
    // tr, br, tl
    // br, bl, tl
    // init buffers
    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // load and bind texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, numChannels;
    unsigned char* data = stbi_load("game_data/sprites/PlayerSprites.png", &width, &height, &numChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("file failed to load\n");
    }
    stbi_image_free(data);
    engine.renderer.atlasTexture = texture;
    // shader compilation
    int  success;
    char infoLog[512];
    unsigned int vertexShader, fragmentShader, shaderProgram;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = (const char*) simple_vert_script; // stupid type conversion
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Shader compilation failed\n%s\n", infoLog);
    }
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = (const char*) simple_frag_script;
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Shader compilation failed\n%s\n", infoLog);
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
    // bind vertex attributes
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
}