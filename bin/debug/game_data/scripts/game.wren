import "engine" for Engine
import "node" for Node
import "input" for Input
import "window" for Window
import "renderer" for Renderer
import "audio_system" for AudioSystem
import "tilemap" for TileMap
import "vmath" for Transform

class Game is Node {
    construct new(){
        super()
        var trans = Transform.new()
        trans.position.x = 10
        trans.position.y = 5
        System.print(trans.position.length)

        _x = 384
        _y = 0
        _speed = 1
        Renderer.addSprite()
        Renderer.setSpriteDimensions(0, 0, 0, 1024, 1024)
        Renderer.setSpriteTransform(0, _x, 0, 0, 1024, 1024, 0)
        
        // Renderer.addSprite()
        // Renderer.setSpriteDimensions(1, 0, 0, 24, 24)
        // Renderer.setSpriteTransform(1, 24, 0, 0, 24, 24, 0)
        // Renderer.blitSpriteToAtlas(1)
        // setFrame(0)
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
        // _tileMap = TileMap.new(16, 10, 18, 18, 0, tracker)
        // _tileMap.addTemplate(0, 72, false)
        // for (x in 0..15) {
        //     for(y in 0..9){
        //         if (x == 0 || x == 15 || y == 0 || y == 9){
        //             _tileMap.setTile(0, x, y)
        //         }
        //     }
        // }
        AudioSystem.addAudioSource()
        AudioSystem.loadAudioSource(0, "game_data/sfx/Climb_Rope_Loop_00.wav")
        AudioSystem.setGainAudioSource(0, 50)
        // var sprStats = Renderer.blitFileToAtlas("game_data/sprites/characters_packed.png", 0, 0)
        // tracker = tracker + sprStats["height"]
        // Renderer.blitFileToAtlas("game_data/sprites/characters_packed.png", 0, tracker)
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
        var dx = 0
        var dy = 0
        if (Input.getButton("left", 0)){
            dx = dx - _speed
        }
        if (Input.getButton("right", 0)){
            dx = dx + _speed
        }
        if (Input.getButton("up", 0)){
            dy = dy - _speed
        }
        if (Input.getButton("down", 0)){
            dy = dy + _speed
        }
        _x = _x + dx
        _y = _y + dy
        Renderer.setSpriteTransform(0, _x, _y, 0, 1024, 1024, 0)
        // it's important to call the super method
        // typically after we have handled our own updates
        // that way if we change a child it will update accordingly *this* tick
        super.update(deltaTime)
    }
}