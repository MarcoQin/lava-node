import * as core from './build/Release/lava_node.node'

export namespace Core {
    core.global_init()
    export function loadFile(filePath:string) {
        core.load_file(filePath)
    }
    
    export function pause() {
        core.pause()
    }

    export function stop() {
        core.stop()
    }

    export function setVolume(volume: number) {
        core.set_volume(volume)
    }
}