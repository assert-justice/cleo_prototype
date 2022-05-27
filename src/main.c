// Cleo Virtual Console
// created at: 2022-05-16
// Copyright (C) 2022 Riley Miller

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include "wren/wren.h"
#include "wren_help/wren_help.h"
#include "glad/gles2.h"
#include "GLFW/glfw3.h"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    printf("hello\n");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// int main(int argc, char* argv[]){
int main(){
    // WrenVM* vm = wrenHelpInit();
    glfwSetErrorCallback(error_callback);
    if(!glfwInit()){
        printf("glfw failed to init");
    }
    GLFWwindow* window = glfwCreateWindow(640, 480, "Cleo", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    gladLoadGLES2(glfwGetProcAddress);
    while (!glfwWindowShouldClose(window))
    {
        // Keep running
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}