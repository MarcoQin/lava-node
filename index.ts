import * as core from './build/Release/lava_node.node'

export function globalInit() {
    core.global_init()
}

export function loadFile(filePath: string) {
    core.load_file(filePath)
}