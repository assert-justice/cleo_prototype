import "engine" for Engine
import "node" for Node
import "input" for Input
import "window" for Window
import "renderer" for Renderer

class Game is Node {
    update(deltaTime){
        if(Input.getButtonPressed("cancel", 0)){
            Engine.quit()
        }
        if(Input.getButtonPressed("special", 0)){
            // System.print("hello")
            // System.print()
            // var stats = Window.getStats()
            // stats["fullScreen"] = true
            // Window.setStats(stats)
            // Renderer.setClearColor(0.2, 0.3, 0.3)
            // var val = Renderer.addSprite()
            // System.print(val)
            setFrame(_frame + 1)
        }
        // it's important to call the super method
        // typically after we have handled our own updates
        // that way if we change a child it will update accordingly *this* tick
        super.update(deltaTime)
    }
    construct new(){
        super()
        Renderer.addSprite()
        setFrame(0)
        Renderer.blitFileToAtlas("game_data/sprites/characters_packed.png", 0, 24)
    }
    setFrame(frame){
        _frame = frame
        Renderer.setSpriteDimensions(0, 24 * _frame, 24, 24, 24)
        Renderer.setSpriteTransform(0, _frame * 8, 0, 0, 24, 24, 0)
    }
}