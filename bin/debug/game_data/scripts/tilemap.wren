import "renderer" for Renderer
import "sprite" for Sprite
import "vmath" for Vector3

class TileMap is Sprite{
    construct new(parent, width, height, cellWidth, cellHeight, spriteX, spriteY){
        super(parent, spriteX, spriteY, width * cellWidth, height * cellHeight)
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
        for (i in 0...height) {
            var row = []
            for (f in 0...width) {
                row.add(null)
            }
            _tiles.add(row)
        }
        // request a brush sprite 
        _brushSprite = Renderer.addSprite()
        if (_brushSprite == -1){
            Fiber.abort("Not enough sprites for tilemap")
        }
        
        Renderer.setSpriteDimensions(_brushSprite, 0, 0, cellWidth, cellHeight)
        Renderer.setSpriteTransform(_brushSprite, 0, 0, 0, cellWidth, cellHeight, 0)
    }
    width{_width}
    height{_height}
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
        _tiles[y][x] = [idx, solid]
    }
    solid(x, y){
        var val = _tiles[y][x]
        if(val && val[1]) return true
        return false
    }
    onGrid(x, y){
        return x >= 0 && x < _width && y >= 0 && y < _height
    }
    getCellAtPosition(position){
        var cell = position.copy().subVector(transform.position).addVector(transform.origin)
        cell.x = (cell.x / _cellWidth).floor
        cell.y = (cell.y / _cellHeight).floor
        var tile = _tiles[cell.y][cell.x]
        return [cell.x, cell.y, tile ? tile[0] : null, tile ? tile[1] : null]
    }
    raycast(start, direction, length){
        // DDA algorithm
        // (not yet implemented)
        // inspired by https://github.com/OneLoneCoder/olcPixelGameEngine/blob/master/Videos/OneLoneCoder_PGE_RayCastDDA.cpp
    }
    collide(position, velocity, boxWidth, boxHeight){
        // assume current position is clear
        var minX = -Num.infinity
        var minY = -Num.infinity
        var maxX = Num.infinity
        var maxY = Num.infinity
        var left = (position.x / _cellWidth).floor
        // var right = left + 1
        var right = ((position.x + boxWidth) / _cellWidth).floor
        var top = (position.y / _cellHeight).floor
        var bottom = ((position.y + boxHeight) / _cellHeight).floor
        // check left and right sides
        for (y in top..bottom) {
            if(solid(left-1,y)){
                minX = left * _cellWidth
            }
            if(solid(right+1,y)){
                maxX = (right+1) * _cellWidth - boxWidth - 1
            }
        }
        // check top and bottom sides
        for (x in left..right) {
            if(solid(x, top-1)){
                minY = top * _cellHeight
            }
            if(solid(x, bottom+1)){
                maxY = (bottom+1) * _cellHeight - boxHeight - 1
            }
        }
        return Vector3.new((position.x + velocity.x).clamp(minX, maxX), (position.y + velocity.y).clamp(minY, maxY), 0)
    }
}