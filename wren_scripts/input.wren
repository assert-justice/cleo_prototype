import "input_codes" for InputBindings
import "vmath" for Vector2

class Input {

    static privateInit(inputs, bindings){
        // just worry about the game modes for now
        // var bindings = {
        //     "confirm": "enter",
        //     "cancel": "escape",
        //     "special": "space",
        //     "up": "w",
        //     "down": "s",
        //     "left": "a",
        //     "right": "d"
        // }
        __baseController = {
            "buttons": [],
            "axis2": []
        }
        __inputState = []
        addController("none", "none", -1) // add aggregate controller
        for (input in inputs) {
            if(!bindings.containsKey(input.key)) continue
            if(input.value["type"] == "button"){
                // do button stuff
                addButton(input.key)
                var keys = bindings[input.key]["keys"]
                for (key in keys) {
                    addKeyToButton(input.key, 0, getKeyCode(key))
                }
            } else if(input.value["type"] == "axis2"){
                // do axis2 stuff
                var deadzone = input.value["deadzone"]
                var filter = input.value["filter"]
                addAxis2(input.key, deadzone, filter)
                var keys = bindings[input.key]["x_axis"]["keys"]
                for (key in keys) {
                    addKeyToAxis2(input.key, 0, getKeyCode(key["name"]), 0, key["mod"])
                }
                keys = bindings[input.key]["y_axis"]["keys"]
                for (key in keys) {
                    addKeyToAxis2(input.key, 0, getKeyCode(key["name"]), 1, key["mod"])
                }
            }
        }
        // for (item in bindings) {
        //     addButton(item.key)
        //     addKeyToButton(item.key, getKeyCode(item.value), 0)
        // }
        // System.print(__inputState)
    }
    static addAxis2(name, deadzone, filter){
        __baseController["axis2"] = [name, deadzone, filter]
        for (controller in __inputState) {
            // vector2, deadzone, filter, key codes[x axis, y axis]
            controller["axis2"][name] = [Vector2.new(0,0), deadzone, filter, [[],[]]]
        }
    }
    static addKeyToAxis2(axisName, controllerIdx, code, axis, mod){
        __inputState[controllerIdx]["axis2"][axisName][3][axis].add([code, mod])
    }
    static addButton(name){
        __baseController["buttons"].add(name)
        for (controller in __inputState) {
            // current state, last state, duration, key codes
            controller["buttons"][name] = [0,0,0,[]]
        }
    }
    static addKeyToButton(buttonName, controllerIdx, code){
        __inputState[controllerIdx]["buttons"][buttonName][3].add(code)
    }
    static addController(bindings, type, joyIndex){
        var controller = {
            "buttons": {},
            "axis2": {}
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
            for (axis2 in controller["axis2"].values) {
                var vec = axis2[0]
                // zero out the axes
                vec.x = 0
                vec.y = 0
                // aggregate the keys
                for (entry in axis2[3][0]) {
                    if(getKey(entry[0])){
                        vec.x = vec.x + entry[1]
                    }
                }
                for (entry in axis2[3][1]) {
                    if(getKey(entry[0])){
                        vec.y = vec.y + entry[1]
                    }
                }
                // apply filtering
                // right now just clamp lengths above 1
                if (vec.length > 1) vec.normalize()
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
        if(!state) System.print(__inputState[controllerIdx]["buttons"])
        return state[0] && !state[1]
    }
    static getButtonReleased(name, controllerIdx){
        // return true if a button was released this tick
        // false otherwise
        var state = getButtonState(name, controllerIdx)
        return !state[0] && state[1]
    }
    static getAxis2(name, controllerIdx){
        return __inputState[controllerIdx]["axis2"][name][0]
    }
}