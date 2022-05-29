import "fs" for FileSystem
import "json" for Json


class Engine {
    static init(){
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
        System.print(settings)
        var newSettings = getSettings()
        System.print(newSettings)
    }
    // foreign static privateInit(settings)
    foreign static privateSetSettings(settings)
    foreign static getSettings()
    // foreign static updateWindow()

}