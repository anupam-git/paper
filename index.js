const path = require("path");
process.env.NODE_CONFIG_DIR = path.join(__dirname, "config");

const {RandomWallpaper} = require(__dirname+"/src/");
const {WallpaperSetter} = require(__dirname+"/src/");
const {SettingsManager} = require(__dirname+"/src");

function RandomWallpaperCLI(resolution, tags) {
    console.log("* Downloading Random Wallpaper from http://unsplash.com");
    console.log(`\t- Resolution : ${resolution}`);
    console.log(`\t- Tags : ${tags}`);
    
    new RandomWallpaper(resolution, tags)
        .fetch()
        .then((imagePath) => {
            WallpaperSetter
                .set(imagePath)
                .then(() => {
                    // Wallpaper Set Successfully
                })
                .catch((err) => {
                    console.log("\tERROR : Could not set wallpaper...");
                    console.log(err);
                });
        })
        .catch((err) => {
            console.log("\tERROR : Could not download wallpaper...");
            console.log(err);
        });
}

module.exports.RandomWallpaperCLI = RandomWallpaperCLI;