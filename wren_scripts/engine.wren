import "fs" for FileSystem
import "json" for Json
import "input" for Input
import "window" for Window
import "renderer" for Renderer

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
            "refreshRate": 0,
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
        Window.privateInit(windowSettings)
        Renderer.privateInit({"width":480,"height":270})
        return FileSystem.read(rootPath)
    }
    static privateReady(root){
        Input.privateInit()
        __root = root
    }
    static update(deltaTime){
        Input.privatePollInputs(deltaTime)
        __root.update(deltaTime)
    }
    foreign static quit()
}