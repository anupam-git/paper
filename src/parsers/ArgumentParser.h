#ifndef PARSER_ARGUMENTPARSER_H
#define PARSER_ARGUMENTPARSER_H

#include <QCommandLineParser>
#include <QStringList>

#include "interactors/FetchWallpaperInteractor.h"

class ArgumentParser {
 private:
  FetchWallpaperInteractor* fetchWallpaperInteractor;
  QCommandLineParser* parser;
  void parseArguments();
  QCommandLineOption *downloadOption, *dirOption, *helpOption,
      *resolutionOption, *refreshRateOption, *saveOption, *tagsOption,
      *versionOption;

 public:
  ArgumentParser();
  void process(QStringList arguments);
};

#endif
