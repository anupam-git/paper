#include "ConfigHelper.h"
#include "parsers/ArgumentParser.h"
#include "utils/CommonUtils.h"

#include <QDebug>

ConfigHelper::ConfigHelper(QCoreApplication* app, QObject* parent)
    : QObject(parent) {
  this->settings = new QSettings();
  this->configValues = new QMap<ConfigEnum, QString>();
  this->commonUtils = new CommonUtils(app);
}

QString ConfigHelper::get(ConfigEnum key) {
  QString instanceValue = this->configValues->value(key);
  QString settingsValue = "";

  if (this->configKeys.contains(key)) {
    settingsValue = this->settings->value(this->configKeys[key][0]).toString();
  }

  if (instanceValue != "") {
    return instanceValue;
  } else if (settingsValue != "") {
    switch (key) {
      case ConfigEnum::DIR:
        if (!ArgumentParser::testDir(settingsValue)) {
          this->commonUtils->sayError(
              "Error accessing directory. Check if you have correct "
              "permissions");
          return "error";
        }
        break;

      case ConfigEnum::REFRESH_RATE:
        if (!ArgumentParser::testRefreshRate(settingsValue)) {
          this->commonUtils->sayError(
              "Invalid Refresh Rate. Input Refresh Rate in the following "
              "format : "
              "n[M|H]");
          return "error";
        }
        break;

      case ConfigEnum::RESOLUTION:
        if (!ArgumentParser::testResolution(settingsValue)) {
          this->commonUtils->sayError(
              "Invalid Resolution. Input Resolution in the following format : "
              "widthxheight");
          return "error";
        }
        break;

      case ConfigEnum::TAGS:
        if (!ArgumentParser::testTags(settingsValue)) {
          this->commonUtils->sayError(
              "Invalid Tags Format. Input Tags as comma seperated values. Eg : "
              "nature,mountain");
          return "error";
        }
        break;
    }

    return settingsValue;
  } else {
    if (key == ConfigEnum::DIR) {
      ArgumentParser::testDir(this->configKeys[key][1]);
    }

    if (this->configKeys.contains(key)) {
      return this->configKeys[key][1];
    } else {
      return "";
    }
  }
}

void ConfigHelper::set(ConfigEnum key, QString value) {
  this->configValues->insert(key, value);
}

void ConfigHelper::setWallpaper(QString wallpaper) {
  this->settings->setValue(this->configKeys[ConfigEnum::WALLPAPER][0],
                           wallpaper);
  this->configValues->insert(ConfigEnum::WALLPAPER, wallpaper);

  this->settings->sync();
}

void ConfigHelper::save() {
  QMapIterator<ConfigEnum, QStringList> iterator(this->configKeys);

  while (iterator.hasNext()) {
    iterator.next();
    QString val = this->configValues->value(iterator.key());
    if (val != "") {
      this->settings->setValue(this->configKeys[iterator.key()][0], val);
    }
  }
}
