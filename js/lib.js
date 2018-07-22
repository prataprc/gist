var util = require('util');
exports.inspect = function(o) {
                    return util.inspect( o, {showHidden: true, depth: null} );
                  };
exports.log = function(o) { console.log( exports.inspect(o) ) };

