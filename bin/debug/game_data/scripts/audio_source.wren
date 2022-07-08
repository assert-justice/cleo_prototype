import "audio_system" for AudioSystem
import "node" for Node
class AudioSource is Node{
    construct new(parent, fname){
        super(parent)
        _handle = AudioSystem.addAudioSource()
        if(_handle == -1) Fiber.abort("Audio source limit exceeded")
        if(!AudioSystem.loadAudioSource(_handle, fname)) Fiber.abort("Cannot load audio file %(fname)")
    }
    play(){
        AudioSystem.playAudioSource(_handle)
    }
    pause(){
        AudioSystem.pauseAudioSource(_handle)
    }
    stop(){
        AudioSystem.stopAudioSource(_handle)
    }
    playing{AudioSystem.audioSourceIsPlaying(_handle)}
    looping{AudioSystem.audioSourceIsLooping(_handle)}
    looping=(val){AudioSystem.loopAudioSource(_handle, val)}
    volume{AudioSystem.getVolumeAudioSource(_handle)}
    volume=(val){AudioSystem.setVolumeAudioSource(_handle, val)}
}