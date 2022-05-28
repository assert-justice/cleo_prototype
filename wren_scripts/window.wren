var default = {
    "name": "Cleo",
    "mode": 0, // 0: windowed, 1: borderless fullscreen, 2: exclusive fullscreen
    "monitor": 0,
    "window_width": 640,
    "window_height": 480,
    "refresh_rate" 0, // 0 indicates maximum availible
    "vsync": true,
    "pixel_mode": 0 // 0: pixel perfect, 1: stretch width, 2: stretch height, 3: stretch both
}

class Window {
    foreign static getSettings()
    foreign static privateSetSettings(settings)
    static setSettings(settings){
        // check for unexpected keys
        for (key in settings.keys){
            if (!default.containsKey(key)){
                Fiber.abort("Unexpected key '%(key)' in settings.json")
            }
        }
        // provide settings with default values if needed
        // for (element in default){
        //     if (!settings.containsKey(element.key)){
        //         settings[element.key] = element.value
        //     }
        // }
    }
    static setDefaultSettings(){
        privateSetSettings(default)
    }
}