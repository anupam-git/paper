const wallpaper = require('wallpaper');
 
function set(filepath) {
    return wallpaper.set(filepath);
}

module.exports.set = set;