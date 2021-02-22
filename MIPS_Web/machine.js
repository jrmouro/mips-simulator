var spawn = require('child_process').spawn;
var ls  = spawn('../MIPS/dist/Debug/GNU-Linux/./mips', []);

ls.stdout.on('data', function (data) {
   console.log(data);
});


// const fs = require('fs');

// fs.readFile('dd3dfa66-92f8-4940-aa8b-94bc0e5f81af.json', 'utf8', (err, jsonString) => {
//     if (err) {
//         console.log("Error reading file from disk:", err);
//         return;
//     }
//     try {
//         var obj = JSON.parse(jsonString); 
//         console.log("obj is:", obj) ;
//     } 
//         catch(err) {
//         console.log('Error parsing JSON string:', err)
//     }
// });