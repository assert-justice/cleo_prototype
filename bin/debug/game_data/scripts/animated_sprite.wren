import "sprite" for Sprite

class AnimatedSprite is Sprite {
    construct new(parent, offset, dimensions, fps){
        super(parent, offset.x, offset.y, dimensions.x, dimensions.y)
        _anim = [[offset, dimensions]]
        _animations = {}
        _playing = false
        this.fps = fps
        _frame = 0
        _looping = true
        _reversed = false
        _bounce = false
    }
    fps{1 / _frameTime}
    fps=(val){
        _frameTime = 1 / val
        _frameClock = _frameTime
    }
    looping{_looping}
    looping=(val){_looping = val}
    playing{_playing}
    play(name){
        _anim = _animations[name]
        _frame = 0
        _frameClock = _frameTime
        _playing = true
    }
    pause(){
        _playing = false
    }
    stop(){
        _playing = false
        _frame = 0
        offset = _anim[_frame][0]
        dimensions = _anim[_frame][1]
    }
    // reversed{_reversed}
    // reversed=(val){_reversed = val}
    // bounce{_bounce}
    // bounce=(val){_bounce = val}
    newAnim(name){
        _animations[name] = []
    }
    addFrame(name, offset, dimensions){
        _animations[name].add([offset, dimensions])
        return _animations[name].count
    }
    update(deltaTime){
        super.update(deltaTime)
        if(!_playing) return
        _frameClock = _frameClock - deltaTime
        if (_frameClock <= 0){
            _frame = _frame + 1
            _frameClock = _frameTime
            if (_frame == _anim.count){
                _frame = 0
                if (!_looping) {
                    _playing = false
                    return
                }
            }
            offset = _anim[_frame][0]
            dimensions = _anim[_frame][1]
        }
    }
}