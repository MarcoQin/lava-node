"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var core = require("./build/Release/lava_node.node");
var Core;
(function (Core) {
    core.global_init();
    function loadFile(filePath) {
        core.load_file(filePath);
    }
    Core.loadFile = loadFile;
})(Core = exports.Core || (exports.Core = {}));
//# sourceMappingURL=index.js.map