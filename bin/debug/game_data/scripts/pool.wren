class Pool {
    construct new(startSize, fn){
        _avail = []
        _fn = fn
        for (i in 0...startSize) {
            _avail.add(alloc())
        }
    }
    alloc(){
        var node = _fn.call()
        node.pool = this

        _avail.add(node)
        return node
    }
    get(parent){
        var node = null
        if(_avail.count > 0){
            node = _avail.removeAt(_avail.count-1)
        } else{
            node = alloc()
        }
        node.setParent(parent)
        node.wake()
        return node
    }
    free(node){
        _avail.add(node)
        // parent connections should be broken when freeing a pooled object
        node.setParent(null)
    }
}