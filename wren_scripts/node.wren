class Node {
    construct new(){
        _xPosition = 0
        _yPosition = 0
        _parent = null
        _children = []
        _awake = false
        _visible = false
        _lastVisible = false
        wake()
    }
    update(deltaTime){
        // update children
        for (child in _children) {
            child.update(deltaTime)
        }
    }
    wake(){
        // use to set the initial state
        _awake = true
        _visible = true
    }
    sleep(){
        // use to clean up a node so it can be reused
        _awake = false
        _visible = false
    }
    addChild(child){
        child.setParent(this)
    }
    setParent(parent){
        // might as well check if the parent is already correct
        if (_parent == parent){
            return
        }
        // remove self from current parent if any
        if (_parent){
            _parent.children.remove(this)
            // do any other needed cleanup
        }
        // set new parent
        _parent = parent
        // add self to new parent's children if not already
        _parent.children.add(this)
    }
}