# Random Wallpaper CLI
> A CLI Tool to set a random wallpaper from Unsplash.com

Works on macOS, Linux, and Windows.

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/anupam-git/random-wallpaper-cli/master/LICENSE) [![npm version](https://badge.fury.io/js/random-wallpaper-cli.svg)](https://badge.fury.io/js/random-wallpaper-cli) [![GitHub stars](https://img.shields.io/github/stars/anupam-git/random-wallpaper-cli.svg)](https://github.com/anupam-git/random-wallpaper-cli/stargazers)

## Install

```
$ npm install -g random-wallpaper-cli
```

## Usage

```
Usage: random-wallpaper-cli [arguments]
A CLI Tool to set a random wallpaper from Unsplash.com

Arguments:
  --resolution=widthxheight         Provide the resolution of the wallpaper to be downloaded
                                    Default value : 1920x1080

  --tags=[comma seperated tags]     Provide tags to filter wallpaper search results
                                    Example :   --tags=nature
                                                --tags=water,mountain

  --refresh-rate=N[M|H]             Specify Refresh rate in minutes or hours
                                    Example :   --refresh-rate=5M    Will refresh every 5 minutes
                                                --refresh-rate=2H    Will refresh every 2 hours
                                                
Examples:
    $> random-wallpaper-cli --help
    $> random-wallpaper-cli
    $> random-wallpaper-cli --resolution=1024x768
    $> random-wallpaper-cli --resolution=1024x768 --tags=road,mountain
    $> random-wallpaper-cli --resolution=1024x768 --tags=road,mountain --refresh-rate=30M
    $> random-wallpaper-cli --resolution=1920x1080 --refresh-rate=1H
```

## License

MIT © Anupam Basak