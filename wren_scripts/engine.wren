import "fs" for FileSystem
import "json" for Json
import "input" for Input
import "window" for Window

class Engine {
    static privateInit(){
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
            "title": "Cleo",
            "fullScreen": false,
            "monitorIndex": 0,
            "width": 800,
            "height": 600,
            "refreshRate": 0, // 0 indicates maximum availible
            "vsync": true,
            // "pixelMode": 0, // 0: pixel perfect, 1: stretch width, 2: stretch height, 3: stretch both
            // "internalWidth": 400,
            // "internalHeight": 200,
        }
        // load settings if availible
        var windowSettings = {}
        // if (FileSystem.fileExists("settings.json")){
        //     settings = Json.parse(FileSystem.read("settings.json"))
        // }
        // // for missing settings use default
        for (element in defaultWindow){
            if (!windowSettings.containsKey(element.key)){
                windowSettings[element.key] = element.value
            }
        }
        // System.print("yo")
        Window.privateInit(windowSettings)
        // set the state of the engine struct
        // privateSetSettings(settings)
        // var newSettings = getSettings()
        return FileSystem.read(rootPath)
        // return {
        //     "rootSrc": FileSystem.read(rootPath),
        //     "windowSettings": windowSettings
        // }
    }
    static privateReady(root){
        Input.privateInit()
        __root = root
        // Engine.privateLaunch()
    }
    static update(deltaTime){
        Input.privatePollInputs(deltaTime)
        __root.update(deltaTime)
    }
    // foreign static privateLaunch()
    // foreign static privateSetSettings(settings)
    // foreign static getSettings()
    // foreign static updateWindow()
    foreign static quit()
}