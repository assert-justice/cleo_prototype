class Vector2 {
    construct new(x, y){
        new(x, y, [true])
    }
    construct new(x, y, flag){
        _comps = [x, y]
        _dirty = flag
    }
    length {
        var len = 0
        for (comp in comps) {
            len = len + comp * comp
        }
        return len.sqrt
    }
    x {comps[0]}
    x=(val){
        comps[0] = val
        dirty = true
    }
    y {comps[1]}
    y=(val){
        comps[1] = val
        dirty = true
    }
    comps{_comps}
    dirty{_dirty[0]}
    dirty=(val){_dirty[0] = val}
}

class Vector3 is Vector2 {
    construct new(x, y, z){
        new(x, y, z, [true])
    }
    construct new(x, y, z, flag){
        _comps = [x, y, z]
        _dirty = flag
    }
    z {comps[2]}
    z=(val){
        comps[2] = val
        dirty = true
    }
    comps{_comps}
    dirty{_dirty[0]}
    dirty=(val){_dirty[0] = val}}

class Transform {
    construct new(){
        _dirty = [true]
        _position = Vector3.new(0, 0, 0, _dirty)
        _scale = Vector2.new(0, 0, _dirty)
        _angle = 0
    }
    position{_position}
    position=(val){
        _position = val
        System.print("here")
        dirty = true
    }
    scale{_scale}
    scale=(val){
        _scale = val
        dirty = true
    }
    angle{_angle}
    angle=(val){
        _angle = val
        dirty = true
    }
    dirty{_dirty[0]}
    dirty=(val){_dirty[0] = val}
}