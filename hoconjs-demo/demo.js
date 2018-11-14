var parseHocon = require('hocon-parser');
var someHoconText = "a = 2 \
                    a : 4 \
                    b = [2, 3, 4] \
                    b = [2, 5] \
                    c { c1 : 5 } \
                    d : Hello \
                    e: \"Hello World\" \
                    f: [ \
                      \"F1\" \
                      \"F2\" \
                      \"F3\" \
                      \"F4\" \
                    ]";
var obj = parseHocon(someHoconText);
console.log(obj);