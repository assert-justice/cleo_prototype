#ifndef INPUT
#define INPUT
#include "GLFW/glfw3.h"
typedef struct {
    int keyCode;
    int state;
    int lastState;
    int duration;
} Button;

typedef struct {
    Button buttons[20];
    int buttonCount;
} Input;
#endif
