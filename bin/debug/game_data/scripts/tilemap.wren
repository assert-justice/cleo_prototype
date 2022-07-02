import "renderer" for Renderer

class TileMap {
    construct new(width, height, cellWidth, cellHeight, spriteX, spriteY){
        _width = width
        _height = height
        _cellWidth = cellWidth
        _cellHeight = cellHeight
        _totalWidth = width * cellWidth
        _totalHeight = height * cellHeight
        _spriteX = spriteX
        _spriteY = spriteY
        _tileTemplates = []
        _tiles = []
        for (i in 0..height) {
            var row = []
            for (f in 0..width) {
                row.add(null)
            }
            _tiles.add(row)
        }
        // request two sprites, a brush sprite and a sprite for the whole map
        _baseSprite = Renderer.addSprite()
        _brushSprite = Renderer.addSprite()
        if (_baseSprite == -1 || _brushSprite == -1){
            Fiber.abort("Not enough sprites for tilemap")
        }
        Renderer.setSpriteDimensions(_baseSprite, spriteX, spriteY, _totalWidth, _totalHeight)
        Renderer.setSpriteTransform(_baseSprite, 0, 0, 0, _totalWidth, _totalHeight, 0)
        
        Renderer.setSpriteDimensions(_brushSprite, 0, 0, cellWidth, cellHeight)
        Renderer.setSpriteTransform(_brushSprite, 0, 0, 0, cellWidth, cellHeight, 0)
    }
    addTemplate(xOffset, yOffset, solid){
        _tileTemplates.add([xOffset, yOffset, solid])
        return _tileTemplates.count - 1
    }
    setTile(idx, x, y){
        if (idx < 0 || idx >= _tileTemplates.count){
            Fiber.abort("%(idx) is not a valid tile index.")
        }
        // draw tile
        var tile = _tileTemplates[idx]
        var xOffset = tile[0]
        var yOffset = tile[1]
        var solid = tile[2]
        Renderer.setSpriteDimensions(_brushSprite, xOffset, yOffset, _cellWidth, _cellHeight)
        Renderer.setSpriteTransform(_brushSprite, x * _cellWidth + _spriteX, y * _cellHeight + _spriteY, 0, _cellWidth, _cellHeight, 0)
        Renderer.blitSpriteToAtlas(_brushSprite)
        // add tile to tiles
        tiles[y][x] = [idx, solid]
    }
}