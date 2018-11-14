var parseHocon = require('hocon-parser');
var fs = require('fs');

var content = fs.readFileSync('module.conf', 'utf8');
var obj = parseHocon(content);
console.log(JSON.stringify(obj));

// merge
console.log('\nmerge test\n');
var dev = fs.readFileSync('conf_dev.conf', 'utf8');
var proj = fs.readFileSync('conf_proj.conf', 'utf8');
obj = parseHocon(dev + '\n' + proj);
console.log(JSON.stringify(obj));

