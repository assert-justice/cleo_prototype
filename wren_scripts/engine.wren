import "fs" for FileSystem
import "json" for Json
import "input" for Input

class Engine {
    static init(){
        var folderName = "game_data"
        var manifestPath = "%(folderName)/manifest.json"
        if (!FileSystem.fileExists(manifestPath)){
            Fiber.abort("no manifest found at '%(manifestPath)'")
        }
        var manifest = Json.parse(FileSystem.read(manifestPath))
        var rootPath = "%(folderName)/%(manifest["main"])"
        if (!FileSystem.fileExists(rootPath)){
            Fiber.abort("no main file found at '%(rootPath)'")
        }
        var defaultWindow = {
            "name": "Cleo",
            "windowMode": 0, // 0: windowed, 1: borderless fullscreen, 2: exclusive fullscreen
            "monitor": 0,
            "windowWidth": 800,
            "windowHeight": 600,
            "refreshRate": 0, // 0 indicates maximum availible
            "vsync": true,
            "pixelMode": 0, // 0: pixel perfect, 1: stretch width, 2: stretch height, 3: stretch both
            "internalWidth": 400,
            "internalHeight": 200,
        }
        // load settings if availible
        var settings = {}
        // if (FileSystem.fileExists("settings.json")){
        //     settings = Json.parse(FileSystem.read("settings.json"))
        // }
        // // for missing settings use default
        for (element in defaultWindow){
            if (!settings.containsKey(element.key)){
                settings[element.key] = element.value
            }
        }
        // set the state of the engine struct
        privateSetSettings(settings)
        var newSettings = getSettings()
        return FileSystem.read(rootPath)
    }
    static privateSetRoot(root){
        Input.privateInit()
        __root = root
    }
    foreign static privateSetSettings(settings)
    foreign static getSettings()
    // foreign static updateWindow()
    foreign static quit()
}