import "input_codes" for InputBindings

class Input {

    static privateInit(){
        // TODO: actually read input settings from the user
        var bindings = {
            "confirm": "enter",
            "cancel": "escape",
            "special": "space"
        }
        __baseController = {
            "buttons": []
        }
        __inputState = []
        addController("none", "none", -1) // add aggregate controller
        for (item in bindings) {
            addButton(item.key)
            addKeyToButton(item.key, getKeyCode(item.value), 0)
        }
        // System.print(__inputState)
    }
    static addButton(name){
        __baseController["buttons"].add(name)
        for (controller in __inputState) {
            controller["buttons"][name] = [0,0,0,[]]
        }
    }
    static addKeyToButton(buttonName, code, controllerIdx){
        __inputState[controllerIdx]["buttons"][buttonName][3].add(code)
        // controller["buttons"][buttonName] = code
    }
    static addController(bindings, type, joyIndex){
        var controller = {
            "buttons": {}
        }
        __inputState.add(controller)
    }
    foreign static getKey(code)
    static privatePollInputs(deltaTime){
        for (controller in __inputState) {
            for (button in controller["buttons"].values) {
                // move the current state to the last state
                button[1] = button[0]
                button[0] = false
                // aggregate the keys
                for (code in button[3]) {
                    button[0] = button[0] || getKey(code)
                }
                // update the duration
                if (button[0] == button[1]){
                    button[2] = button[2] + deltaTime
                } else {
                    button[2] = 0
                }
            }
        }
    }
    // foreign static getMouseButton(code)
    // foreign static getJoyButton(code)
    // foreign static getJoyAxis(code)
    static getKeyCode(key){
        if (!InputBindings.keyToCode.containsKey(key)) {
            Fiber.abort("'%(key)' is not a valid key name")
        }
        return InputBindings.keyToCode[key]
    }
    // validateButton(name){
    //     if (!__inputState.containsKey(name)){
    //         Fiber.abort("no button named '%(name)' has been configured")
    //     }
    // }
    static getButtonState(name, controllerIdx){
        // validateButton(name)
        return __inputState[controllerIdx]["buttons"][name]
    }
    static getButton(name, controllerIdx){
        // return 0 if a button is not currently pressed
        // otherwise return the duration it has been pressed
        return getButtonState(name, controllerIdx)[0]
    }
    static getButtonPressed(name, controllerIdx){
        // return true if a button was pressed this tick
        // false otherwise
        var state = getButtonState(name, controllerIdx)
        return state[0] && !state[1]
    }
    static getButtonReleased(name, controllerIdx){
        // return true if a button was released this tick
        // false otherwise
        var state = getButtonState(name, controllerIdx)
        return !state[0] && state[1]
    }
}