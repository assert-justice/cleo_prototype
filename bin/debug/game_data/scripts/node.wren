import "vmath" for Transform

class Node {
    construct new(parent){
        _tranform = Transform.new()
        _parent = parent
        _children = []
        _awake = false
        _visible = false
        _lastVisible = false
        _pool = null
        setParent(parent)
        wake()
    }
    pool=(val){
        _pool = val
    }
    transform{_tranform}
    transform=(val){_tranform = val}
    awake{_awake}
    visible{_visible && _lastVisible}
    setVisible(val){_visible = val}
    update(deltaTime){
        // update children
        for (child in _children) {
            child.update(deltaTime)
        }
        _lastVisible = _visible
    }
    wake(){
        // use to set the initial state
        _awake = true
        setVisible(true)
        for (child in _children) {
            child.wake()
        }
    }
    sleep(){
        // use to clean up a node so it can be reused
        _awake = false
        _visible = false
        if(_pool) _pool.free(this)
        for (child in _children) {
            child.sleep()
        }
    }
    addChild(child){
        // check if the node is already a child
        if (_children.indexOf(child) != -1) return
        _children.add(child)
        child.privateSetParent(this)
    }
    removeChild(child){
        // ensure the node is actually a child
        var idx = _children.indexOf(child)
        if(idx == -1) Fiber.abort("Tried to remove child '%(child)' from a node that is not its parent.")
        _children.removeAt(idx)
    }
    privateSetParent(parent){
        _parent = parent
    }
    setParent(parent){
        if(parent == null){
            if (_parent){
                // if node has a parent remove from current parent's children
                _parent.removeChild(this)
            } 
            return
        }
        parent.addChild(this)
    }
    getChildren(){_children}
}