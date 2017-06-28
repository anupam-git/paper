const fs = require('fs-extra');
const request = require('request');
const config = require("config");
const path = require("path");
const os = require("os");

class RandomWallpaper {    
    constructor(resolution, tags) {
        this.resolution = resolution;
        this.tags = tags;
    }

    fetch() {
        return new Promise((resolve, reject) => {
            const uri = config.get("randomImageBaseUrl")+"/"+this.resolution+"/?"+this.tags;
            const imageDir = path.join(os.homedir(), config.get("cachePath"), config.get("imagesCacheFolder"));
            const imagePath = path.join(imageDir, config.get("imageFileName"));

            request.head(uri, (err, res, body) => {
                let req = request(uri);
                req
                    .on("response", () => {
                        fs.emptyDirSync(imageDir);
                        req.pipe(fs.createWriteStream(imagePath))
                    })
                    .on("error", (err) => {
                        reject(err);
                    })
                    .on("close", () => {
                        resolve(imagePath);
                    });
            });
        });
    }
}

module.exports = RandomWallpaper;