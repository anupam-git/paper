#include "ArgumentParser.h"

ArgumentParser::ArgumentParser() {
  this->parser = new QCommandLineParser();
  this->parser->setApplicationDescription(PROJECT_DESCRIPTION);
  this->parser->addHelpOption();
  this->parser->addOptions(
      {{{"d", "download"}, "Only download the wallpaper"},
       {{"D", "dir"},
        "Directory to download the wallpaper to"
        "\nDefault value : .cache/paper/"
        "\nExample       : --dir ~/foo/bar"
        "\n                 -d ~/foooo/baaaar"},
       {{"r", "resolution"},
        "Provide the resolution of the wallpaper to be downloaded"
        "\nDefault value : 1920x1080"
        "\nExample       : --resolution 1024x768"
        "\n                 -r 1920x1080",
        "[widthxheight"},
       {{"R", "refresh-rate"},
        "Refreshes Wallpaper every 'n' Minutes or 'n' Hours"
        "\nDefault value : 1920x1080"
        "\nExample       : --refresh-rate 5 M"
        "\n                 -R 2 H",
        "n M|H"},
       {{"s", "save"},
        "Save the provided configuration to file"
        "\nWill be used to remember user preference"},
       {{"t", "tags"},
        "Provide tags to filter wallpaper search results"
        "\nExample       : -t water,mountain"
        "\n                 --tags nature",
        "comma seperated tags]"}});
  this->parser->addVersionOption();
}

QCommandLineParser* ArgumentParser::getParser() {
  return this->parser;
}
