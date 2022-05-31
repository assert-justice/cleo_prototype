import "input_codes" for keyToCode, codeToKey

class Input {

    static privateInit(){
        // TODO: actually read input settings from the user
        var bindings = {
            "confirm": "enter",
            "cancel": "escape",
            "special": "space"
        }
        __inputState = {}
        for (item in bindings) {
            privateAddButton(item.key, getKeyCode(item.value))
            __inputState[item.key] = [0, 0, 0]
        }
    }
    // foreign static privatePollInputs()
    // foreign static privateAddButton(name, code)
    static getKeyCode(key){
        if (!keyToCode.containsKey(key)) {
            Fiber.abort("'%(key)' is not a valid key name")
        }
        return keyToCode[key]
    }
    validateButton(name){
        if (!__inputState.containsKey(name)){
            Fiber.abort("no button named '%(name)' has been configured")
        }
    }
    getButtonState(name){
        validateButton(name)
        return __inputState[name]
    }
    getButton(name){
        // return 0 if a button is not currently pressed
        // otherwise return the duration it has been pressed
        var state = getButtonState(name)
        if (state[0]) return state[2]
        return 0
    }
    getButtonPressed(name){
        // return true if a button was pressed this tick
        // false otherwise
        var state = getButtonState(name)
        return state[0] && !state[1]
    }
    getButtonReleased(name){
        // return true if a button was released this tick
        // false otherwise
        var state = getButtonState(name)
        return !state[0] && state[1]
    }
}