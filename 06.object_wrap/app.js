/**
 * Created by kelvinsun on 2015/10/21.
 */
var addon = require('./build/Release/addon');

var obj = new addon.MyObject(10);
console.log(obj.plusOne());
console.log(obj.plusOne());
console.log(obj.plusOne());

var obj2 = addon.MyObject(1);
console.log(obj2.plusOne());
console.log(obj2.getValue());
console.log(obj2.multiply(2).getValue());
console.log(obj2.getValue());