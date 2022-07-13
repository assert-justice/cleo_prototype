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
        _hflip = false
        _vflip = false
    }
    hflip{_hflip}
    hflip=(val){
        _hflip = val
        _dirty[0] = true
    }
    vflip{_vflip}
    vflip=(val){
        _vflip = val
        _dirty[0] = true
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
            Renderer.setSpriteDimensions(_handle, _offset.x + (hflip ? _dimensions.x : 0), _offset.y + (vflip ? _dimensions.y : 0), _dimensions.x - (hflip ? _dimensions.x * 2 : 0), _dimensions.y - (vflip ? _dimensions.y * 2 : 0))
            _dirty[0] = false
        }
            // System.print(transform.dirty)
        if (transform.dirty){
            transform.dirty = false
            var tempOrigin = Vector2.new(transform.origin.x, transform.origin.y)
            tempOrigin.rotate(transform.angle)
            Renderer.setSpriteTransform(_handle, 
                transform.position.x - tempOrigin.x, 
                transform.position.y - tempOrigin.y, 
                transform.position.z,
                //visible ? transform.position.z : 200, // if invisible set z outside of the clip plane
                transform.scale.x * _dimensions.x, 
                transform.scale.y * _dimensions.y, 
                transform.angle)
        }
        super.update(deltaTime)
    }
}