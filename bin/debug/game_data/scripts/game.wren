import "engine" for Engine
import "node" for Node
import "input" for Input

class Game is Node {
    update(deltaTime){
        // it's important to call the super method
        // typically after we have handled our own updates
        // that way if we change a child it will update accordingly *this* tick
        if(Input.getButton("special")){
            Engine.quit()
        }
        super.update(deltaTime)
    }
    // static init(){
    //     Fiber.abort("got here")
    // }
    construct new(){
        super()
    }
}