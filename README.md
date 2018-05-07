# Paper - A Random Wallpaper Application
> A CLI Tool to set a random wallpaper from Unsplash.com

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/anupam-git/paper/master/LICENSE) [![GitHub stars](https://img.shields.io/github/stars/anupam-git/paper.svg)](https://github.com/anupam-git/paper/stargazers)

## Install

TODO

## Usage

```
Usage: ./paper [options]

Paper - A Random Wallpaper Application
A CLI Tool to set a random wallpaper from Unsplash.com

Options:
  -h, --help                          Displays this help.
  -d, --download                      Only download the wallpaper
  -D, --dir                           Directory to download the wallpaper to
                                      Default value : .cache/paper/
                                      Example       : --dir ~/foo/bar
                                                      -d ~/foooo/baaaar
  -r, --resolution <[widthxheight>    Provide the resolution of the wallpaper
                                      to be downloaded
                                      Default value : 1920x1080
                                      Example       : --resolution 1024x768
                                                      -r 1920x1080
  -R, --refresh-rate <n M|H>          Refreshes Wallpaper every 'n' Minutes or
                                      'n' Hours
                                      Default value : 1920x1080
                                      Example       : --refresh-rate 5 M
                                                      -R 2 H
  -s, --save                          Save the provided configuration to file
                                      Will be used to remember user preference
  -t, --tags <comma seperated tags]>  Provide tags to filter wallpaper search
                                      results
                                      Example       : -t water,mountain
                                                      --tags nature
  -v, --version                       Displays version information.
```

## License

MIT © Anupam Basak
