import "engine" for Engine, Window, Input, Renderer

import "input_codes" for InputCodes

class Main {
    static init(){
        __esc = InputCodes.keyToCode["escape"]
        var defaultWindow = {
            "title": "Cleo",
            "fullScreen": false,
            "monitorIndex": 0,
            "width": 960,
            "height": 540,
            "refreshRate": 0,
            "vsync": true
        }
        Window.init(defaultWindow)
        Renderer.init({"width":480,"height":270})
        Renderer.blitFileToAtlas("game_data/sprites/characters_packed.png", 0, 0)
        Renderer.addSprite()
        Renderer.setSpriteDimensions(0, 0, 0, 24, 24)
        Renderer.setSpriteTransform(0, 0, 0, 0, 24, 24, 0)
    }
    static update(deltaTime){
        if (Input.getKey(__esc)) Engine.quit()
    }
}