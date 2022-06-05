#include "renderer.h"
#include "../engine/engine.h"
#include "stdio.h"
#include "../shader_inc.h"

extern Engine engine;

void framebufferCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void setClearColor(float red, float green, float blue){
    glClearColor(red, green, blue, 1.0f);
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(engine.renderer.shaderProgram);
    glBindVertexArray(engine.renderer.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void initRenderer(){
    glfwSetFramebufferSizeCallback(engine.window, framebufferCallback);
    glViewport(0, 0, engine.windowStats.width, engine.windowStats.height);
    float vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f,  0.5f, 0.0f, // top left

        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f,  0.5f, 0.0f, // top left
        -0.5f, -0.5f, 0.0f, // bottom left
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    engine.renderer.VAO = VAO;
    engine.renderer.shaderProgram = shaderProgram;
}