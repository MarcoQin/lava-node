import * as core from "./build/Release/lava_node.node";

core.global_init();

export function loadFile(filePath: string) {
  core.load_file(filePath);
}

export function pause() {
  core.pause();
}

export function stop() {
  core.stop();
}

export function setVolume(volume: number) {
  core.set_volume(volume);
}

export function isStopping(): boolean {
  if (core.is_stopping()) {
    return true;
  }
  return false;
}

export function seekByPercent(percent: number) {
  core.seek_by_percent(percent);
}

export function seekBySec(sec: number) {
  core.seek_by_sec(sec);
}

export function getTimeLength(): number {
  return core.get_time_length();
}

export function getCurrentTimePos(): number {
  return core.get_current_time_pos();
}
