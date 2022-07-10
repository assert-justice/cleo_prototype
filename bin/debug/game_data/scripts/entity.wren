import "node" for Node

class Entity is Node {
    // entities have attached sprites, colliders and groups, health and damage functions
    construct new(parent){
        super(parent)
        _health = 100
    }
    damage(amount, source){
        _health = _health - amount
        if (_health < 0){
            die()
        }
    }
    die(){
        sleep()
    }
}