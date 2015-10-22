/**
 * Created by kelvinsun on 2015/10/22.
 */

var createObject = require('./build/Release/addon');

var obj = createObject(10);

console.log(obj.plusOne());
console.log(obj.plusOne());
console.log(obj.plusOne());

var obj2 = createObject(2);

console.log(obj2.plusOne());
console.log(obj2.plusOne());
console.log(obj2.plusOne());