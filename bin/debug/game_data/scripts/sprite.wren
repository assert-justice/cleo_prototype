import "node" for Node
import "renderer" for Renderer
import "vmath" for Vector2, Vector3

class Sprite is Node {
    construct new(parent, xOffset, yOffset, width, height){
        super(parent)
        _handle = Renderer.addSprite()
        if(_handle == -1){
            Fiber.abort("not enough sprites")
        }
        _dirty = [true]
        _offset = Vector2.new(xOffset, yOffset, _dirty)
        _dimensions = Vector2.new(width, height, _dirty)
    }
    offset{_offset}
    offset=(val){
        _offset = val
        _dirty[0] = true
    }
    dimensions{_dimensions}
    dimensions=(val){
        _dimensions = val
        _dirty[0] = true
    }
    update(deltaTime){
        if(_dirty[0]){
            Renderer.setSpriteDimensions(_handle, _offset.x, _offset.y, _dimensions.x, _dimensions.y)
            _dirty[0] = false
        }
            // System.print(transform.dirty)
        if (transform.dirty){
            transform.dirty = false
            Renderer.setSpriteTransform(_handle, 
                transform.position.x, 
                transform.position.y, 
                transform.position.z, 
                transform.scale.x * _dimensions.x, 
                transform.scale.y * _dimensions.y, 
                transform.angle)
        }
        super.update(deltaTime)
    }
}