var addon = require('./build/Release/addon');

var obj1 = addon('hello');
var obj2 = addon('world');

console.log(obj1, obj2);
