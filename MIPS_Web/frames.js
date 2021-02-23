var fs = require('fs');
const { spawn } = require('child_process');

async function getMipsFrames(id, mem_words, code) {

    return new Promise(

        (resolve, reject) => {

            fs.writeFile(
                id + ".txt",
                code,
                function (err) {

                    if (err) {
                        reject(err);
                        return;
                    }

                    var mips = spawn('../MIPS/dist/Debug/GNU-Linux/mips', [id + ".txt", id + ".json", "" + mem_words])

                    mips.stdout.on('data', (data) => {
                        console.log(`stdout: ${data}`);
                    });

                    mips.stderr.on('data', (data) => {
                        console.error(`stderr: ${data}`);
                    });

                    mips.on('close', (exit_code) => {
                        console.log(`child process exited with code ${exit_code}`);
                        if (exit_code == 0) {
                            fs.readFile(
                                id + ".json",
                                'utf8',
                                (err, jsonString) => {
                                    if (err) {
                                        reject(err);
                                        return;
                                    }
                                    try {
                                        var frames = { 
                                            self: JSON.parse(jsonString), 
                                            id: id, 
                                            code: code, 
                                            current: 0,
                                            mem_words: mem_words
                                        };
                                        resolve(frames);
                                    }
                                    catch (err) {
                                        reject(err);
                                        return;
                                    }
                                }
                            );
                        } else {

                            reject(new Error("child process mips exited with code " + exit_code));
                            return;

                        }
                    });

                }
            );

            this.clock = 0;

        }

    );

}

module.exports = getMipsFrames;

