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
        _x = 384
        _y = 0
        _speed = 3
        _atlas = Sprite.new(this, 0,0,1024, 1024)
        _atlas.transform.position.x = _x
        _atlas.transform.position.y = _y
        _vel = Vector3.new(0, 0, 0)
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
        _tileMap = TileMap.new(this, 16, 10, 18, 18, 0, tracker)
        _tileMap.addTemplate(0, 72, false)
        for (x in 0...16) {
            for(y in 0...10){
                if (x == 0 || x == 15 || y == 0 || y == 9){
                    _tileMap.setTile(0, x, y)
                }
            }
        }
        AudioSystem.addAudioSource()
        AudioSystem.loadAudioSource(0, "game_data/sfx/Climb_Rope_Loop_00.wav")
        AudioSystem.setGainAudioSource(0, 50)
    }
    update(deltaTime){
        if(Input.getButtonPressed("cancel", 0)){
            Engine.quit()
        }
        if(Input.getButtonPressed("special", 0)){
            // System.print("hello")
            // System.print()
            // var stats = Window.getStats()
            // stats["fullScreen"] = true
            // Window.setStats(stats)
            // Renderer.setClearColor(0.2, 0.3, 0.3)
            // var val = Renderer.addSprite()
            // System.print(val)
            // setFrame(_frame + 1)
            AudioSystem.playAudioSource(0)
        }
        _vel.x = 0
        _vel.y = 0
        if (Input.getButton("left", 0)){
            _vel.x = _vel.x - 1
        }
        if (Input.getButton("right", 0)){
            _vel.x = _vel.x + 1
        }
        if (Input.getButton("up", 0)){
            _vel.y = _vel.y - 1
        }
        if (Input.getButton("down", 0)){
            _vel.y = _vel.y + 1
        }
        _vel.normalize().mulScalar(_speed)
        _atlas.transform.position.x = _atlas.transform.position.x + _vel.x
        _atlas.transform.position.y = _atlas.transform.position.y + _vel.y
        // it's important to call the super method
        // typically after we have handled our own updates
        // that way if we change a child it will update accordingly *this* tick
        super.update(deltaTime)
    }
}