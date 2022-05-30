import "imput_codes" for keyToCode, codeToKey

class InputSystem {

    static init(){
        // TODO: actually read input settings from the user
        var bindings = {
            "confirm": "enter",
            "cancel": "escape",
            "special": "space"
        }
    }
    static getKeyCode(key){
        if (!keyToCode.containsKey(key)) {
            Fiber.abort("'%(key)' is not a valid key name")
        }
        return keyToCode[key]
    }
}