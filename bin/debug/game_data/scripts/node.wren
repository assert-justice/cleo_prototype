import "vmath" for Transform

class Node {
    construct new(parent){
        _tranform = Transform.new()
        _parent = parent
        _children = []
        _awake = false
        _visible = false
        _lastVisible = false
        setParent(parent)
        wake()
    }
    transform{_tranform}
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
        _visible = true
    }
    sleep(){
        // use to clean up a node so it can be reused
        _awake = false
        _visible = false
    }
    addChild(child){
        // check if the node is already a child
        if (_children.indexOf(child) != -1) return
        _children.add(child)
        child.privateSetParent(this)
    }
    privateSetParent(parent){
        _parent = parent
    }
    setParent(parent){
        if(parent == null) return
        parent.addChild(this)
    }
    getChildren(){_children}
}