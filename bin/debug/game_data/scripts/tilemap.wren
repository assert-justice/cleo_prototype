import "renderer" for Renderer

class TileMap {
    construct new(width, height, cellWidth, cellHeight){
        // request two sprites, a brush sprite and a sprite for the whole map
        _baseSprite = Renderer.addSprite()
        _brushSprite = Renderer.addSprite()
        if (_baseSprite == -1 || _brushSprite == -1){
            Fiber.abort("Not enough sprites for tilemap")
        }
    }
}