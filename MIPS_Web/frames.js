var fs = require('fs');
const { spawn, spawnSync } = require('child_process');

function frames(id) {

    this.vector = [];
    this.id = id;
    this.clock = 0;

    this.get_current_frame = function () {

        return this.vector[this.clock];

    }

    this.get_next_frame = function () {

        if (this.clock < this.vector.length - 1)
            this.clock++;

        return this.vector[this.clock];

    }

    this.get_first_frame = function () {

        this.clock = 0;

        return this.vector[this.clock];

    }

    this.get_last_frame = function () {

        this.clock = this.vector.length - 1;

        return this.vector[this.clock];

    }

    var self = this;

    this.exec = function (mem_size, code) {

        fs.writeFile(
            self.id + ".txt",
            code,
            function (err) {
                if (err) return console.log(err);
            }
        );

        var mips = spawn('../MIPS/dist/Debug/GNU-Linux/mips', [self.id + ".txt", self.id + ".json", "" + mem_size])

        mips.stdout.on('data', (data) => {
            console.log(`stdout: ${data}`);
        });

        mips.stderr.on('data', (data) => {
            console.error(`stderr: ${data}`);
        });

        mips.on('close', (code) => {
            console.log(`child process exited with code ${code}`);
            if (code == 0) {
                fs.readFile(
                    self.id + ".json",
                    'utf8',
                    (err, jsonString) => {
                        if (err) {
                            console.log("Error reading file from disk:", err);
                            return;
                        }
                        try {
                            self.vector = JSON.parse(jsonString);
                        }
                        catch (err) {
                            console.log('Error parsing JSON string:', err)
                        }
                    }
                );
            }
        });

        this.clock = 0;

    }

    this.exec(16, "");

}

module.exports = frames;