const {RandomWallpaper} = require(__dirname+"/src/");
const {WallpaperSetter} = require(__dirname+"/src/");
const {SettingsManager} = require(__dirname+"/src");

let isShowUsage = false;
let resolution = SettingsManager.get("resolution", true);
let tags = SettingsManager.get("tags", true);
let resolutionTestRegex = /\d+x\d+/;
let tagsTestRegex = /^\w+(,\w+)*$/;

process.argv.forEach(function (val, index, array) {
    if (index > 1) {
        let prop = val.split("=");
        let propKey = prop[0],
            propVal = prop[1];


        switch (propKey) {
            case "--resolution":
                if (resolutionTestRegex.test(propVal)) {
                    resolution = propVal;
                } else {
                    isShowUsage = true
                }

                break;

            case "--tags":
                if (tagsTestRegex.test(propVal)) {
                    tags = propVal;
                } else {
                    isShowUsage = true
                }
                
                break;            

            case "--help":
                isShowUsage = true;

                break;
        }
    }
});

if (!isShowUsage) {
    console.log("* Downloading Random Wallpaper from http://unsplash.com");
    console.log(`\t- Resolution : ${resolution}`);
    console.log(`\t- Tags : ${tags}`);
    
    new RandomWallpaper(resolution, tags)
        .fetch()
        .then((imagePath) => {
            console.log("\n\tWallpaper Downloaded Successfully...");

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
} else {
    let helpMessage = `Usage: random-wallpaper-cli [arguments]
A CLI Tool to set a random wallpaper from Unsplash.com

Arguments:
  --resolution=widthxheight           Provide the resolution of the wallpaper to be downloaded
                                      Default value : 1920x1080

  --tags=[comma seperated tags]       Provide tags to filter wallpaper search results
                                      Example :   --tags=nature
                                                  --tags=water,mountain
                                                
Example:
    $> random-wallpaper-cli
    $> random-wallpaper-cli --resolution=1024x768
    $> random-wallpaper-cli --resolution=1024x768 --tags=road,mountain`;

    console.log(helpMessage);
}