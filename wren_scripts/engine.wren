// import "fs" for FileSystem
// import "json" for Json
// import "input" for Input
// import "window" for Window
// import "renderer" for Renderer

class Engine {
    // static privateInit(){
    //     var folderName = "game_data"
    //     var manifestPath = "%(folderName)/manifest.json"
    //     if (!FileSystem.fileExists(manifestPath)){
    //         Fiber.abort("no manifest found at '%(manifestPath)'")
    //     }
    //     var manifest = Json.parse(FileSystem.read(manifestPath))
    //     var rootPath = "%(folderName)/%(manifest["main"])"
    //     if (!FileSystem.fileExists(rootPath)){
    //         Fiber.abort("no main file found at '%(rootPath)'")
    //     }
    //     var defaultWindow = {
    //         "title": "Cleo",
    //         "fullScreen": false,
    //         "monitorIndex": 0,
    //         "width": 960,
    //         "height": 540,
    //         "refreshRate": 0,
    //         "vsync": true
    //     }
    //     // load settings if availible
    //     var settingsPath = "%(folderName)/%(manifest["settings"])"
    //     var windowSettings = {}
    //     if (FileSystem.fileExists(settingsPath)){
    //         windowSettings = Json.parse(FileSystem.read(settingsPath))
    //     }
    //     // // for missing settings use default
    //     for (element in defaultWindow){
    //         if (!windowSettings.containsKey(element.key)){
    //             windowSettings[element.key] = element.value
    //         }
    //     }
    //     Window.privateInit(windowSettings)
    //     // Renderer.privateInit({"width":960,"height":540})
    //     Renderer.privateInit({"width":480,"height":270})
    //     var inputsPath = "%(folderName)/%(manifest["inputs"])"
    //     var inputs = null
    //     if (FileSystem.fileExists(inputsPath)){
    //         inputs = Json.parse(FileSystem.read(inputsPath))
    //     }
    //     var bindingsPath = "%(folderName)/%(manifest["input_bindings"])"
    //     var bindings = null
    //     if (FileSystem.fileExists(bindingsPath)){
    //         bindings = Json.parse(FileSystem.read(bindingsPath))
    //     }
    //     Input.privateInit(inputs, bindings)
    //     return FileSystem.read(rootPath)
    // }
    // static privateReady(root){
    //     __root = root
    // }
    // static getRoot(){
    //     return __root
    // }
    // static update(deltaTime){
    //     Input.privatePollInputs(deltaTime)
    //     __root.update(deltaTime)
    // }
    foreign static quit()
    foreign static enableLogging(fname)
}

class Audio {
    foreign static addAudioSource()
    foreign static loadAudioSource(idx, fname)
    foreign static getNumAudioSources()
    foreign static getMaxAudioSources()
    foreign static playAudioSource(idx)
    foreign static pauseAudioSource(idx)
    foreign static stopAudioSource(idx)
    foreign static audioSourceIsPlaying(idx)
    foreign static loopAudioSource(idx, shouldLoop)
    foreign static audioSourceIsLooping(idx)
    foreign static setVolumeAudioSource(idx, volume)
    foreign static getVolumeAudioSource(idx)
}

class File {
    foreign static fileExists(path)
    foreign static read(path)
    foreign static write(path, text)
}

class Input {
    foreign static getKey(code)
    // foreign static getMouseButton(code)
    // foreign static getMouseX(code)
    // foreign static getMouseY(code)
    // foreign static getJoyButton(code)
    // foreign static getJoyAxis(code)
}

class Renderer {
    foreign static init(settings)
    foreign static setClearColor(red, green, blue)
    foreign static addSprite()
    foreign static getNumSprites()
    foreign static getMaxSprites()
    foreign static setSpriteDimensions(idx, xOffset, yOffset, width, height)
    foreign static setSpriteTransform(idx, xPos, yPos, zPos, xScale, yScale, angle)
    foreign static setChildSpriteTransform(parentId, childId, xPos, yPos, zPos, xScale, yScale, angle)
    foreign static blitFileToAtlas(fname, xOffset, yOffset)
    foreign static blitSpriteToAtlas(idx)
}

class Window {
    foreign static init(settings)
    foreign static setStats(settings)
    foreign static getStats()
}