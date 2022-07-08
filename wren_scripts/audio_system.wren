class AudioSystem {
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