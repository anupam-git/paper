const path = require("path");
const os = require("os");
const config = require("config");
const fs = require("fs-extra");

const settingsPath = path.join(os.homedir(), config.get("cachePath"), config.get("settingsFileName"));
const defaultSettings = require(__dirname+"/settings.json");

if (fs.existsSync(settingsPath)) {
    // Settings File Exists

    try {
        settings = require(settingsPath);

        for (key in defaultSettings) {
            if (settings[key] == undefined) {
                // Key not found in Settings File. Use Default Value.

                settings[key] = defaultSettings[key];
            }
        }
    } catch (err) {
        // Error Reading Settings File. Use Default Value.

        settings = defaultSettings;
    }
} else {
    // Settings File Does Not Exists. Use Default Value.

    settings = defaultSettings;
}

function get(key) {
    return settings[key];
}

function set(key, value) {
    settings[key] = value;

    fs.writeFileSync(settingsPath, JSON.stringify(settings, null, 4));
}

module.exports.get = get;
module.exports.set = set;