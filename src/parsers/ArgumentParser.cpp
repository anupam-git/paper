#include "ArgumentParser.h"

#include <QCommandLineOption>
#include <QDir>
#include <QRegularExpression>
#include <QDebug>
#include <QProcess>
#include <QFile>

ArgumentParser::ArgumentParser(QCoreApplication* app,
                               CommonUtils* commonUtils,
                               ConfigHelper* configHelper,
                               QObject* parent)
    : QObject(parent) {
  this->app = app;
  this->commonUtils = commonUtils;
  this->configHelper = configHelper;

  /**** CREATE ARGUMENTS ****/
  this->parser = new QCommandLineParser();
  this->parser->setApplicationDescription(PROJECT_DESCRIPTION);
  this->downloadOption =
      new QCommandLineOption(this->argumentKeys[ArgumentEnum::DOWNLOAD],
                             "Only download the wallpaper\n");
  this->dirOption =
      new QCommandLineOption(this->argumentKeys[ArgumentEnum::DIR],
                             "Directory to download the wallpaper"
                             "\nDefault dir : .local/share/Paper/paper"
                             "\nExample : --dir ~/foo/bar"
                             "\n           -D ~/foooo/baaaar\n",
                             "directory_path");
  this->helpOption = new QCommandLineOption(
      this->argumentKeys[ArgumentEnum::HELP], "Displays this help\n");
  this->resolutionOption =
      new QCommandLineOption(this->argumentKeys[ArgumentEnum::RESOLUTION],
                             "Resolution of the wallpaper to be downloaded"
                             "\nDefault resolution : 1920x1080"
                             "\nExample : --resolution 1024x768"
                             "\n           -r 1920x1080\n",
                             "widthxheight");
  this->refreshRateOption = new QCommandLineOption(
      this->argumentKeys[ArgumentEnum::REFRESH_RATE],
      "Refreshes Wallpaper every 'n' Minutes or 'n' Hours"
      "\nExample : --refresh-rate 5M"
      "\n           -R 2H\n",
      "n[M|H]");
  this->saveOption =
      new QCommandLineOption(this->argumentKeys[ArgumentEnum::SAVE],
                             "Save the [dir, resolution, tags] to file"
                             "\nWill be used to remember user preference\n");
  this->startDaemonOption =
      new QCommandLineOption(this->argumentKeys[ArgumentEnum::START_DAEMON],
                             "Start as daemon"
                             "\nTo be used with --refresh-rate option\n");
  this->stopDaemonOption = new QCommandLineOption(
      this->argumentKeys[ArgumentEnum::STOP_DAEMON], "Stop the daemon\n");
  this->tagsOption =
      new QCommandLineOption(this->argumentKeys[ArgumentEnum::TAGS],
                             "Provide tags to filter wallpaper search results"
                             "\nExample : --tags nature"
                             "\n           -t water,mountain\n",
                             "comma seperated tags");
  this->versionOption =
      new QCommandLineOption(this->argumentKeys[ArgumentEnum::VERSION],
                             "Displays version information\n");

  this->parser->addOption(*this->downloadOption);
  this->parser->addOption(*this->dirOption);
  this->parser->addOption(*this->helpOption);
  this->parser->addOption(*this->resolutionOption);
  this->parser->addOption(*this->refreshRateOption);
  this->parser->addOption(*this->saveOption);
  this->parser->addOption(*this->startDaemonOption);
  this->parser->addOption(*this->stopDaemonOption);
  this->parser->addOption(*this->tagsOption);
  this->parser->addOption(*this->versionOption);
  /**** //// END CREATE ARGUMENTS //// ****/
}

int ArgumentParser::process() {
  QStringList arguments = this->app->arguments();
  this->parser->parse(arguments);

  return this->parseArguments();
}

bool ArgumentParser::isStartDaemon() {
  return this->parser->isSet(*this->startDaemonOption);
}

bool ArgumentParser::isStopDaemon() {
  return this->parser->isSet(*this->stopDaemonOption);
}

bool ArgumentParser::showHelp() {
  return this->parser->isSet(*this->helpOption) ||
         this->parser->isSet(*this->versionOption);
}

bool ArgumentParser::testResolution(QString resolution) {
  QRegularExpression resolutionRegex("^\\d+x\\d+$");

  return resolutionRegex.match(resolution).hasMatch();
}

bool ArgumentParser::testRefreshRate(QString refreshRate) {
  QRegularExpression refreshRateRegex("^\\d+[MH]$");

  return refreshRateRegex.match(refreshRate).hasMatch();
}

bool ArgumentParser::testTags(QString tags) {
  QRegularExpression tagsRegex("\\w*,*");

  return tagsRegex.match(tags).hasMatch();
}

bool ArgumentParser::testDir(QString dirPath) {
  QDir dir(dirPath);

  if (!dir.exists()) {
    if (!dir.mkpath(".")) {
      return false;
    }
  }

  return true;
}

int ArgumentParser::parseArguments() {
  if (this->parser->isSet(*this->dirOption)) {
    QString dirPath = this->parser->value(*this->dirOption);

    if (this->testDir(dirPath)) {
      this->configHelper->set(ConfigEnum::DIR, dirPath);
    } else {
      this->commonUtils->sayError(
          "Error accessing directory. Check if you have correct permissions");
      return 1;
    }
  }
  if (this->parser->isSet(*this->resolutionOption)) {
    QString resolution = this->parser->value(*this->resolutionOption);
    if (this->testResolution(resolution)) {
      this->configHelper->set(ConfigEnum::RESOLUTION, resolution);
    } else {
      this->commonUtils->sayError(
          "Invalid Resolution. Input Resolution in the following format : "
          "widthxheight");
      return 1;
    }
  }
  if (this->parser->isSet(*this->refreshRateOption)) {
    QString refreshRate = this->parser->value(*this->refreshRateOption);

    if (this->testRefreshRate(refreshRate)) {
      this->configHelper->set(ConfigEnum::REFRESH_RATE, refreshRate);
    } else {
      this->commonUtils->sayError(
          "Invalid Refresh Rate. Input Refresh Rate in the following format : "
          "n[M|H]");
      return 1;
    }
  }
  if (this->parser->isSet(*this->tagsOption)) {
    QString tags = this->parser->value(*this->tagsOption);

    if (this->testTags(tags)) {
      this->configHelper->set(ConfigEnum::TAGS, tags);
    } else {
      this->commonUtils->sayError(
          "Invalid Tags Format. Input Tags as comma seperated values. Eg : "
          "nature,mountain");
      return 1;
    }
  }

  if (this->parser->isSet(*this->helpOption)) {
    this->parser->showHelp();
    return 0;
  }
  if (this->parser->isSet(*this->versionOption)) {
    this->parser->showVersion();
    return 0;
  }

  if (this->parser->isSet(*this->downloadOption)) {
    this->configHelper->set(ConfigEnum::DOWNLOAD, "true");
  }
  if (this->parser->isSet(*this->saveOption)) {
    this->configHelper->save();
  }

  QFile pidFile(
      QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation) +
      "/paper.pid");
  pidFile.open(QIODevice::ReadOnly);

  if (pidFile.isReadable() && !this->showHelp() && this->isStartDaemon()) {
    this->commonUtils->sayError(
        "Daemon is already Running. To stop the running daemon run "
        "`paper --stop-daemon`.");

    exit(1);
  } else if (pidFile.isReadable() && !this->showHelp() &&
             !this->isStopDaemon()) {
    this->commonUtils->sayWarning(
        "Daemon is already Running. To stop the running daemon run "
        "`paper --stop-daemon`.");
    this->commonUtils->say("");
  }

  if (this->parser->isSet(*this->startDaemonOption)) {
    if (!this->parser->isSet(*this->refreshRateOption)) {
      this->commonUtils->sayError(
          "Invalid Options. --start-daemon is to be used with --refresh-rate "
          "option");

      return 1;
    }

    QStringList arguments = this->app->arguments();
    QString program = arguments[0];
    QProcess* process = new QProcess(this);
    qint64 pid;

    arguments.removeAt(0);
    arguments.removeAt(arguments.indexOf("--start-daemon"));

    process->setStandardOutputFile(QProcess::nullDevice());
    process->setStandardErrorFile(QProcess::nullDevice());
    process->setProgram(program);
    process->setArguments(arguments);
    process->setWorkingDirectory(QDir::currentPath());
    process->startDetached(&pid);

    QFile pidFile(
        QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation) +
        "/paper.pid");
    pidFile.open(QIODevice::WriteOnly);
    pidFile.write(QVariant(pid).toString().toStdString().c_str());

    this->commonUtils->say("Daemon Initialized");
  }
  if (this->parser->isSet(*this->stopDaemonOption)) {
    QFile pidFile(
        QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation) +
        "/paper.pid");
    pidFile.open(QIODevice::ReadWrite);

    QProcess::startDetached(
        "kill " + QString::fromStdString(pidFile.readAll().toStdString()));
    pidFile.remove();

    return 0;
  }

  if (this->configHelper->get(ConfigEnum::DIR) == "error" ||
      this->configHelper->get(ConfigEnum::RESOLUTION) == "error" ||
      this->configHelper->get(ConfigEnum::REFRESH_RATE) == "error" ||
      this->configHelper->get(ConfigEnum::TAGS) == "error") {
    return 1;
  }

  return 0;
}
