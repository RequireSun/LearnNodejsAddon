/**
 * Created by kelvinsun on 2015/10/21.
 */
var addon = require('./build/Release/addon');

var fn = addon();
console.log(fn, fn());