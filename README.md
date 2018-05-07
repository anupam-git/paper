# Paper - A Random Wallpaper Application
> A CLI Tool to set a random wallpaper from Unsplash.com

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/anupam-git/paper/master/LICENSE) [![GitHub stars](https://img.shields.io/github/stars/anupam-git/paper.svg)](https://github.com/anupam-git/paper/stargazers)

## Install

TODO

## Usage

```
Usage: paper [arguments]

Arguments:
  --help, -h                              Print this help message
  
  --tags, -t [comma seperated tags]       Provide tags to filter wallpaper search results
                                          Example       : --tags nature
                                                          -t water,mountain
  
  --resolution, -r [widthxheight]         Provide the resolution of the wallpaper to be downloaded
                                          Default value : 1920x1080
                                          Example       : --resolution 1024x768
                                                          -r 1920x1080
  
  --download, -d                          Only download the wallpaper
                                          Example       : --download
                                                          -d
  
  --dir, -D [path]                        Directory to download the wallpaper to
                                          Default value : .cache/paper/
                                          Example       : --dir ~/foo/bar
                                                          -d ~/foooo/baaaar
  
  --save, -s                              Save the provided configuration to file
                                          Will be used to remember user preference
                                          Example       : --save
                                                          -s

  --refresh-rate, -R n[M|H]               Refreshes Wallpaper every 'n' Minutes or 'n' Hours
                                          Example       : --refresh-rate 5M # Will refresh every 5 minutes
                                                          --R 2H            # Will refresh every 2 hours
                                                
Example:
  $> paper --tags road,mountain --resolution 1024x768 --refresh-rate 30M --save
```

## License

MIT © Anupam Basak
