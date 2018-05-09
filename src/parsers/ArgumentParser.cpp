#include "ArgumentParser.h"
#include "interactors/FetchWallpaperInteractor.h"

#include <QCommandLineOption>

ArgumentParser::ArgumentParser() {
  this->parser = new QCommandLineParser();
  this->parser->setApplicationDescription(PROJECT_DESCRIPTION);
  this->downloadOption = new QCommandLineOption(
      {"d", "download"}, "Only download the wallpaper\n");
  this->dirOption =
      new QCommandLineOption({"D", "dir"},
                             "Directory to download the wallpaper"
                             "\nDefault dir        : .cache/paper/"
                             "\nExample            : --dir ~/foo/bar"
                             "\n                      -D ~/foooo/baaaar\n");
  this->helpOption =
      new QCommandLineOption({"h", "help"}, "Displays this help\n");
  this->resolutionOption =
      new QCommandLineOption({"r", "resolution"},
                             "Resolution of the wallpaper to be downloaded"
                             "\nDefault resolution : 1920x1080"
                             "\nExample            : --resolution 1024x768"
                             "\n                      -r 1920x1080\n",
                             "widthxheight");
  this->refreshRateOption = new QCommandLineOption(
      {"R", "refresh-rate"},
      "Refreshes Wallpaper every 'n' Minutes or 'n' Hours"
      "\nExample            : --refresh-rate 5M"
      "\n                      -R 2H\n",
      "n[M|H]");
  this->saveOption =
      new QCommandLineOption({"s", "save"},
                             "Save the provided configuration to file"
                             "\nWill be used to remember user preference\n");
  this->tagsOption =
      new QCommandLineOption({"t", "tags"},
                             "Provide tags to filter wallpaper search results"
                             "\nExample            : --tags nature"
                             "\n                      -t water,mountain\n",
                             "comma seperated tags");
  this->versionOption = new QCommandLineOption(
      {"v", "version"}, "Displays version information\n");

  this->parser->addOption(*this->downloadOption);
  this->parser->addOption(*this->dirOption);
  this->parser->addOption(*this->helpOption);
  this->parser->addOption(*this->resolutionOption);
  this->parser->addOption(*this->refreshRateOption);
  this->parser->addOption(*this->saveOption);
  this->parser->addOption(*this->tagsOption);
  this->parser->addOption(*this->versionOption);

  this->fetchWallpaperInteractor = new FetchWallpaperInteractor();
}

void ArgumentParser::process(QStringList arguments) {
  this->parser->parse(arguments);
  this->parseArguments();
}

void ArgumentParser::parseArguments() {
  if (this->parser->isSet(*this->downloadOption)) {
    this->fetchWallpaperInteractor->execute();
  }
  if (this->parser->isSet(*this->dirOption)) {
    // TODO
  }
  if (this->parser->isSet(*this->helpOption)) {
    this->parser->showHelp();
  }
  if (this->parser->isSet(*this->resolutionOption)) {
    // TODO
  }
  if (this->parser->isSet(*this->refreshRateOption)) {
    // TODO
  }
  if (this->parser->isSet(*this->saveOption)) {
    // TODO
  }
  if (this->parser->isSet(*this->tagsOption)) {
    // TODO
  }
  if (this->parser->isSet(*this->versionOption)) {
    this->parser->showVersion();
  }
}
