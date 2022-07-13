import "sprite" for Sprite
import "vmath" for Vector3

class Goomba is Sprite {
    construct new(parent, tileMap){
        super(parent, 3 * 24, 2 * 24, 24, 24)
        _tileMap = tileMap
        _gravity = 10
        _speed = 150
        _dx = -1
        _vel = Vector3.new(0,0,0)
    }

    bounce(){
        _dx = -_dx
        hflip = !hflip
    }

    update(deltaTime){
        _vel.x = _dx * _speed * deltaTime
        _vel.y = _vel.y + _gravity * deltaTime
        var newPos = _tileMap.collide(transform.position, _vel, 24, 24)
        if(newPos.x == transform.position.x) bounce()
        if(newPos.y == transform.position.y) _vel.y = 0
        var probe = transform.position.copy()
        probe.x = probe.x + 12
        var cell = _tileMap.getCellAtPosition(probe)
        if(!_tileMap.solid(cell[0] + _dx, cell[1] + 2)) bounce()
        transform.position = newPos
        super.update(deltaTime)
    }
}