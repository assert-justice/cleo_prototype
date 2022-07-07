import "engine" for Engine
import "node" for Node
import "input" for Input
import "window" for Window
import "renderer" for Renderer
import "audio_system" for AudioSystem
import "tilemap" for TileMap
import "sprite" for Sprite
import "vmath" for Vector2, Vector3

class Game is Node {
    construct new(){
        super(null)
        var tracker = 0
        var fnames = [
            "game_data/sprites/characters_packed.png",
            "game_data/sprites/tiles_packed.png",
            "game_data/sprites/kenny_mini_square_mono_12x9.png",
        ]
        for (fname in fnames) {
            var stats = Renderer.blitFileToAtlas(fname, 0, tracker)
            tracker = tracker + stats["height"]
        }
        _tileMap = TileMap.new(this, 27, 15, 18, 18, 0, tracker)
        _tileMap.addTemplate(0, 72, true)
        _tileMap.addTemplate(0, 24, false)
        for (x in 0..._tileMap.width) {
            for(y in 0..._tileMap.height){
                if (x == 0 || x == _tileMap.width-10 || y == 0 || y == _tileMap.height-1){
                    _tileMap.setTile(0, x, y)
                }
            }
        }
        _tileMap.setTile(0, 1, 1)
        _tileMap.setTile(1, 1, 1)
        _x = 100
        _y = 100
        _speed = 200
        _atlas = Sprite.new(this, 0,0,24, 24)
        _atlas.transform.position.x = _x
        _atlas.transform.position.y = _y
        // _atlas = Sprite.new(this, 0,0,1024, 1024)
        // _atlas.transform.position.x = _x
        // _atlas.transform.position.y = _y
        _vel = Vector3.new(0,0,0)
        AudioSystem.addAudioSource()
        AudioSystem.loadAudioSource(0, "game_data/sfx/Climb_Rope_Loop_00.wav")
        AudioSystem.setGainAudioSource(0, 50)
    }
    update(deltaTime){
        if(Input.getButtonPressed("ui_cancel", 0)){
            Engine.quit()
        }
        if(Input.getButtonPressed("fire", 0)){
            AudioSystem.playAudioSource(0)
        }
        var move = Input.getAxis2("move", 0)
        move.mulScalar(_speed * deltaTime)
        _vel.x = move.x
        _vel.y = move.y
        _atlas.transform.position = _tileMap.collide(_atlas.transform.position, _vel, 24, 24)
        // _atlas.transform.position.x = _atlas.transform.position.x + _vel.x
        // _atlas.transform.position.y = _atlas.transform.position.y + _vel.y
        // it's important to call the super method
        // typically after we have handled our own updates
        // that way if we change a child it will update accordingly *this* tick
        super.update(deltaTime)
    }
}