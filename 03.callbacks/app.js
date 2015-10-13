/**
 * Created by kelvin on 15-10-13.
 */

var addon = require('./build/Release/addon');

addon(function (msg) {
    console.log(msg);
});