declare module "*.node" {
    const value: any;
    export default value;
}

declare module "lava-node" {
    export namespace Core {
        export function loadFile(filePath: string) : null
        export function pause() : null
        export function stop() : null
        export function setVolume(volume: number) : null
    }
}