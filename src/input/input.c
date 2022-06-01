#include "input.h"
#include "../engine/engine.h"

// extern Engine engine;

// void init(){
//     // clear any junk data in input
// }

// void pollInputs(){
//     // clear the button states
//     for (size_t i = 0; i < engine.input.buttonCount; i++)
//     {
//         engine.input.buttons[i].lastState = engine.input.buttons[i].state;
//         engine.input.buttons[i].state = 0;
//     }
//     // poll the keys
//     for (size_t i = 0; i < engine.input.keyCount; i++)
//     {
//         int state = glfwGetKey(engine.window, engine.input.keys[i].keyCode);
//         int currentState = engine.input.buttons[engine.input.keys[i].index].state;
//         engine.input.buttons[engine.input.keys[i].index].state = state || currentState;
//     }
//     // finish processing button states
//     for (size_t i = 0; i < engine.input.buttonCount; i++)
//     {
//         int state = engine.input.buttons[i].state;
//         int lastState = engine.input.buttons[i].lastState;
//         int duration = engine.input.buttons[i].duration;
//         // if the states match increment duration. Otherwise set it to 1
//         engine.input.buttons[i].duration = state == lastState ? duration + 1 : 1;
//     }
// }

// void addButton(const char* name){
//     //
//     engine.input.buttons[engine.input.buttonCount] =(Button) {
//         // .keyCode = code,
//         .name = name,
//         .state = 0,
//         .lastState = 0,
//         .duration = 0
//     };
//     engine.input.buttonCount++;
//     engine.input.needsRefresh = 1;
// }

// void bindKeyToButton(int index, int code){
//     engine.input.keys[engine.input.keyCount] = (Key){
//         .keyCode = code,
//         .index = index,
//         .sign = 1,
//         .type = 0
//     };
//     engine.input.keyCount++;
// }