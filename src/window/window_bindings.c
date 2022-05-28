#include "window_bindings.h"

// WrenForeignMethodFn bindWindow(
//   const char* module,
//   const char* className,
//   bool isStatic,
//   const char* signature)
// {
//   if (strcmp(module, "window") == 0){
//     if (strcmp(className, "Engine") == 0){
//       if(strcmp(signature, "privateInit(_)") == 0 && isStatic){
//         return engineInitHook;
//       }
//     }
//   }
//   return NULL;
// }