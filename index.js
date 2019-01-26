"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var core = require("./build/Release/lava_node.node");
function globalInit() {
    core.global_init();
}
exports.globalInit = globalInit;
function loadFile(filePath) {
    core.load_file(filePath);
}
exports.loadFile = loadFile;
//# sourceMappingURL=index.js.map