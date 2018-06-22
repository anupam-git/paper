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
  -d, --download                     Only download the wallpaper

  -D, --dir <directory_path>         Directory to download the wallpaper
                                     Default dir : .local/share/Paper/paper
                                     Example : --dir ~/foo/bar
                                               -D ~/foooo/baaaar

  -h, --help                         Displays this help

  -r, --resolution <widthxheight>    Resolution of the wallpaper to be
                                     downloaded
                                     Default resolution : 1920x1080
                                     Example : --resolution 1024x768
                                               -r 1920x1080

  -R, --refresh-rate <n[M|H]>        Refreshes Wallpaper every 'n' Minutes or
                                     'n' Hours
                                     Example : --refresh-rate 5M
                                               -R 2H

  -s, --save                         Save the [dir, resolution, tags] to file
                                     Will be used to remember user preference

  -S, --start-daemon                 Start as daemon
                                     To be used with --refresh-rate option

  -x, --stop-daemon                  Stop the daemon

  -t, --tags <comma seperated tags>  Provide tags to filter wallpaper search
                                     results
                                     Example : --tags nature
                                               -t water,mountain

  -v, --version                      Displays version information

```

## License

MIT © Anupam Basak
