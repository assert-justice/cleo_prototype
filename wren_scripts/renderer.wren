class Renderer {
    foreign static privateInit(settings)
    foreign static setClearColor(red, green, blue)
    foreign static addSprite()
    foreign static getNumSprites()
    foreign static getMaxSprites()
    foreign static setSpriteDimensions(idx, xOffset, yOffset, width, height)
    foreign static setSpriteTransform(idx, xPos, yPos, zPos, xScale, yScale, angle)
    foreign static blitFileToAtlas(fname, xOffset, yOffset)
    foreign static blitSpriteToAtlas(idx)
}