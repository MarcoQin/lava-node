"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var core = require("./build/Release/lava_node.node");
core.global_init();
function loadFile(filePath) {
    core.load_file(filePath);
}
exports.loadFile = loadFile;
function pause() {
    core.pause();
}
exports.pause = pause;
function stop() {
    core.stop();
}
exports.stop = stop;
function setVolume(volume) {
    core.set_volume(volume);
}
exports.setVolume = setVolume;
function isStopping() {
    if (core.is_stopping()) {
        return true;
    }
    return false;
}
exports.isStopping = isStopping;
function seekByPercent(percent) {
    core.seek_by_percent(percent);
}
exports.seekByPercent = seekByPercent;
function seekBySec(sec) {
    core.seek_by_sec(sec);
}
exports.seekBySec = seekBySec;
function getTimeLength() {
    return core.get_time_length();
}
exports.getTimeLength = getTimeLength;
function getCurrentTimePos() {
    return core.get_current_time_pos();
}
exports.getCurrentTimePos = getCurrentTimePos;
//# sourceMappingURL=index.js.map