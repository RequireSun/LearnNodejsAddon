/**
 * Created by kelvinsun on 2015/10/22.
 */
var addon = require('./build/Release/addon');

var obj1 = addon.createObject(10);
var obj2 = addon.createObject(20);
var result = addon.add(obj1, obj2);

console.log(result);

var obj3 = addon.createObject('30a');
console.log(addon.add(obj1, obj3));