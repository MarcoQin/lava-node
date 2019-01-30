declare module "*.node" {
  const value: any;
  export default value;
}

declare module "lava-node" {
  export function loadFile(filePath: string): null;
  export function pause(): null;
  export function stop(): null;
  export function setVolume(volume: number): null;
  export function isStopping(): boolean;
  export function seekByPercent(percent: number): null;
  export function seekBySec(sec: number): null;
  export function getTimeLength(): number;
  export function getCurrentTimePos(): number;
}
