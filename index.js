const {RandomWallpaper} = require(__dirname+"/src/");
const {WallpaperSetter} = require(__dirname+"/src/");

console.log("* Downloading Random Wallpaper from http://unsplash.com");

new RandomWallpaper(1920, 1080)
    .fetch()
    .then((imagePath) => {
        console.log("\tWallpaper Downloaded Successfully...");

        console.log("\n* Setting Wallpaper");

        WallpaperSetter
            .set(imagePath)
            .then(() => {
                console.log("\tWallpaper Set Successfully...");
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