import "sprite" for Sprite
import "node" for Node
import "vmath" for VMath, Vector2, Vector3
import "input" for Input

class Player is Node {
    construct new(parent, tileMap){
        super(parent)
        _sprite = Sprite.new(this, 0, 0, 24, 24)
        _sprite.transform = transform
        transform.position.x = 100
        transform.position.y = 100
        _tileMap = tileMap
        _vel = Vector3.new(0,0,0)
        _speed = 200
        _gravity = 10
        _jumpSpeed = 400
    }

    update(deltaTime){
        var move = Input.getAxis2("move", 0)
        move.mulScalar(_speed * deltaTime)
        _vel.x = move.x
        _vel.y = _vel.y + _gravity * deltaTime
        if(Input.getButtonPressed("jump", 0)) _vel.y = -_jumpSpeed * deltaTime
        var newPos = _tileMap.collide(transform.position, _vel, 24, 24)
        transform.position = newPos
        super.update(deltaTime)
    }
}