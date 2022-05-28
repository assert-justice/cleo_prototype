import "fs" for FileSystem
import "json" for Json


class Engine {
    static init(){
        var defaultWindow = {
            "name": "Cleo",
            "mode": 0, // 0: windowed, 1: borderless fullscreen, 2: exclusive fullscreen
            "monitor": 0,
            "window_width": 640,
            "window_height": 480,
            "refresh_rate": 0, // 0 indicates maximum availible
            "vsync": true,
            "pixel_mode": 0, // 0: pixel perfect, 1: stretch width, 2: stretch height, 3: stretch both
            "internal_width": 400,
            "internal_height": 200,
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
        privateInit(defaultWindow)
    }

    foreign static privateInit(settings)
}