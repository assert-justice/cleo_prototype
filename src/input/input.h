#ifndef INPUT
#define INPUT
#include "GLFW/glfw3.h"
// at this time input handling is done in the vm
// this isn't great for performance but the implementation is simpler
// might revisit the below later
// typedef struct {
//     const char* name;
//     int state;
//     int lastState;
//     int duration;
// } Button;

// typedef struct {
//     int keyCode;
//     int type;
//     int index;
//     int sign;
// } Key;

// typedef struct {
//     Button buttons[20];
//     int buttonCount;
//     Key keys[20];
//     int keyCount;
//     int needsRefresh;
// } Input;

// void pollInputs();
// void addButton(const char* name);
// void bindKeyToButton(int index, int code);
#endif
