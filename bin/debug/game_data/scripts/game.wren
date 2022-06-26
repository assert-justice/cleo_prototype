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
            var val = Renderer.addSprite()
            System.print(val)
        }
        // it's important to call the super method
        // typically after we have handled our own updates
        // that way if we change a child it will update accordingly *this* tick
        super.update(deltaTime)
    }
    construct new(){
        super()
    }
}