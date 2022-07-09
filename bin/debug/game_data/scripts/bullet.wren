import "sprite" for Sprite
import "vmath" for Vector3, Vector2

class Bullet is Sprite{
    construct new(parent, offset, dimensions, velocity){
        super(parent, offset.x, offset.y, dimensions.x, dimensions.y)
        _velocity = velocity
    }
    update(deltaTime){
        transform.position.addVector(_velocity)
        if(transform.position.y > 200) sleep()
        super.update(deltaTime)
    }
}