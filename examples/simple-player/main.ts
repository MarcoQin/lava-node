import * as Core from "lava-node";
import * as readline from "readline";
import * as process from "process";

let isPlaying = false;

let queue: Array<string> = [];

setInterval(() => {
  if (Core.isStopping() && isPlaying) {
    isPlaying = false;
    console.log("current music is stopping!!");
    if (queue.length > 0) {
      let next = queue.shift();
      if (next) {
        Core.loadFile(next);
        isPlaying = true;
      }
    }
  }
}, 1000);

let rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  prompt: ">>> "
});

rl.prompt();

let volume = 100;

rl.on("line", line => {
  line = line.trim();
  switch (line) {
    case "q":
      rl.close();
      break;
    case "quit":
      rl.close();
      break;
    case "pause":
      Core.pause();
      break;
    case "stop":
      Core.stop();
      break;
    case "volume up":
      volume += 10;
      if (volume > 100) {
        volume = 100;
      }
      Core.setVolume(volume);
      break;
    case "volume down":
      volume -= 10;
      if (volume < 0) {
        volume = 0;
      }
      Core.setVolume(volume);
      break;
    case "next":
      if (queue.length > 0) {
        let next = queue.shift();
        if (next) {
          Core.loadFile(next);
          isPlaying = true;
        }
      }
      break;
    case "total":
      let total = Core.getTimeLength();
      console.log(total);
      break;
    case "pos":
      console.log(Core.getCurrentTimePos());
      break;
  }
  if (line.indexOf("load ") == 0) {
    line = line.replace("load ", "").replace(/\\/g, "");
    console.log(`line is ${line}`);
    if (line != "") {
      Core.loadFile(line);
      isPlaying = true;
    }
  }
  if (line.indexOf("add ") == 0) {
    line = line.replace("add ", "").replace(/\\/g, "");
    console.log(`line is ${line}`);
    if (line != "") {
      if (isPlaying) {
        queue.push(line);
      } else {
        Core.loadFile(line);
        isPlaying = true;
      }
    }
  }

  if (line.indexOf("seek ") == 0) {
    line = line.replace("seek ", "").replace(/\\/g, "");
    console.log(`line is ${line}`);
    if (line != "") {
      let percent = parseFloat(line);
      if (isPlaying) {
        Core.seekByPercent(percent);
      }
    }
  }

  rl.prompt();
}).on("close", () => {
  console.log("exit.");
  process.exit(0);
});
