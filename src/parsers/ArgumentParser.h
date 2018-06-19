#ifndef PARSER_ARGUMENTPARSER_H
#define PARSER_ARGUMENTPARSER_H

#include "helpers/ConfigHelper.h"
#include "utils/CommonUtils.h"

#include <QObject>
#include <QCommandLineParser>
#include <QStringList>

enum class ArgumentEnum {
  DOWNLOAD,
  DIR,
  HELP,
  RESOLUTION,
  REFRESH_RATE,
  SAVE,
  TAGS,
  VERSION
};

class ArgumentParser : public QObject {
  Q_OBJECT

 private:
  QCoreApplication* app;
  CommonUtils* commonUtils;
  ConfigHelper* configHelper;
  QCommandLineParser* parser;
  QCommandLineOption *downloadOption, *dirOption, *helpOption,
      *resolutionOption, *refreshRateOption, *saveOption, *tagsOption,
      *versionOption;
  QMap<ArgumentEnum, QStringList> argumentKeys = {
      {ArgumentEnum::DOWNLOAD, {"d", "download"}},
      {ArgumentEnum::DIR, {"D", "dir"}},
      {ArgumentEnum::HELP, {"h", "help"}},
      {ArgumentEnum::RESOLUTION, {"r", "resolution"}},
      {ArgumentEnum::REFRESH_RATE, {"R", "refresh-rate"}},
      {ArgumentEnum::SAVE, {"s", "save"}},
      {ArgumentEnum::TAGS, {"t", "tags"}},
      {ArgumentEnum::VERSION, {"v", "version"}},
  };
  bool shouldDownloadOnly = false;

  int parseArguments();

 public:
  ArgumentParser(QCoreApplication* app,
                 CommonUtils* commonUtils,
                 ConfigHelper* configHelper,
                 QObject* parent = nullptr);
  int process();
  static bool testResolution(QString resolution);
  static bool testRefreshRate(QString refreshRate);
  static bool testTags(QString tags);
  static bool testDir(QString dirPath);
};

#endif
