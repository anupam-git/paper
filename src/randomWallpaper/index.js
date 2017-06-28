const fs = require('fs-extra');
const request = require('request');
const config = require("config");
const path = require("path");
const os = require("os");

class RandomWallpaper {    
    constructor(width, height, terms) {
        this._resolution = "";

        if (width != null || height != null || width != undefined || height != undefined) {
            this._resolution = `${width}x${height}`;
        }
    }

    get resolution() {
        let res = this._resolution.split("x");

        return [~~res[0], ~~res[1]];
    }

    fetch() {
        return new Promise((resolve, reject) => {
            const uri = config.get("randomImageBaseUrl")+"/"+this._resolution;
            const imageDir = path.join(os.homedir(), config.get("imageCachePath"));
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