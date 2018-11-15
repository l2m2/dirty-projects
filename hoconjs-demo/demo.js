var parseHocon = require('hocon-parser');

var obj = parseHocon('"N.M":2');
console.log(obj);

var fs = require('fs');

var content = fs.readFileSync('lang.conf', 'utf8');
var obj = parseHocon(content);
console.log(obj);

merge
console.log('\nmerge test\n');
var dev = fs.readFileSync('conf_dev.conf', 'utf8');
var proj = fs.readFileSync('conf_proj.conf', 'utf8');
obj = parseHocon(dev + '\n' + proj);
console.log(JSON.stringify(obj));

