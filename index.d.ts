declare module "*.node" {
    const value: any;
    export default value;
}

declare module "lava-node" {
    export namespace Core {
        export function loadFile(filePath: string) : null
    }
}