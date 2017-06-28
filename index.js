const {RandomWallpaper} = require(__dirname+"/src/");
const {WallpaperSetter} = require(__dirname+"/src/");
const {SettingsManager} = require(__dirname+"/src");

const cron = require('node-cron');

let isShowUsage = false;
let resolution = SettingsManager.get("resolution");
let tags = SettingsManager.get("tags");
let resolutionTestRegex = /\d+x\d+/;
let tagsTestRegex = /^\w+(,\w+)*$/;
let refreshRateTestRegex = /^(\d+)[HMS]$/;

process.argv.forEach(function (val, index, array) {
    if (index > 1) {
        let prop = val.split("=");
        let propKey = prop[0],
            propVal = prop[1];

        console.log


        switch (propKey) {
            case "--resolution":
                if (propVal != undefined && resolutionTestRegex.test(propVal)) {
                    resolution = propVal;
                } else {
                    isShowUsage = true
                }

                break;

            case "--tags":
                if (propVal != undefined && tagsTestRegex.test(propVal)) {
                    tags = propVal;
                } else {
                    isShowUsage = true
                }
                
                break;

            case "--refresh-rate":
                if (propVal != undefined && refreshRateTestRegex.test(propVal)) {
                    let cronSettings = "";

                    switch (propVal[propVal.length - 1]) {
                        case "M":
                            let mins = refreshRateTestRegex.exec(propVal)[1];
                            cronSettings = `*/${mins} * * * *`;

                            break;

                        case "H":
                            let hours = refreshRateTestRegex.exec(propVal)[1];
                            cronSettings = `* */${hours} * * *`;

                            break;
                        
                        default:
                            isShowUsage = true;
                    }

                    if (!isShowUsage) {
                        cron.schedule(cronSettings, downloadAndSetWallpaper);
                    }
                } else {
                    isShowUsage = true
                }

                break;

            case "--help":
            default:
                isShowUsage = true;

                break;
        }
    }
});

if (!isShowUsage) {
    downloadAndSetWallpaper();
} else {
    let helpMessage = `Usage: random-wallpaper-cli [arguments]
A CLI Tool to set a random wallpaper from Unsplash.com

Arguments:
  --resolution=widthxheight           Provide the resolution of the wallpaper to be downloaded
                                      Default value : 1920x1080

  --tags=[comma seperated tags]       Provide tags to filter wallpaper search results
                                      Example :   --tags=nature
                                                  --tags=water,mountain

  --refresh-rate=N[M|H]               Specify Refresh rate in minutes or hours
                                      Example :   --refresh-rate=5M     Will refresh every 5 minutes
                                                  --refresh-rate=2H     Will refresh every 2 hours
                                                
Examples:
    $> random-wallpaper-cli --help
    $> random-wallpaper-cli
    $> random-wallpaper-cli --resolution=1024x768
    $> random-wallpaper-cli --resolution=1024x768 --tags=road,mountain
    $> random-wallpaper-cli --resolution=1024x768 --tags=road,mountain --refresh-rate=30M
    $> random-wallpaper-cli --resolution=1920x1080 --refresh-rate=1H`;

    console.log(helpMessage);
}

function downloadAndSetWallpaper() {
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