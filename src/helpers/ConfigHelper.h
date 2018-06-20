#ifndef PARSERS_CONFIGHELPER_H
#define PARSERS_CONFIGHELPER_H

#include <utils/CommonUtils.h>

#include <QObject>
#include <QSettings>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QStandardPaths>

enum class ConfigEnum {
  DIR,
  TAGS,
  RESOLUTION,
  REFRESH_RATE,
  DOWNLOAD,
  WALLPAPER
};

class ConfigHelper : public QObject {
 public:
  ConfigHelper(QCoreApplication* app, QObject* parent = nullptr);
  QString get(ConfigEnum key);
  QStringList getRefreshRate();
  void set(ConfigEnum key, QString value);
  void setWallpaper(QString wallpaper);
  void save();

 private:
  QCoreApplication* app;
  CommonUtils* commonUtils;
  QSettings* settings;

  /**
    * Key : ConfigEnum
    * Value : [Conf Key, Default Value, Should Save to Conf]
    */
  QMap<ConfigEnum, QVariantList> configKeys = {
      {ConfigEnum::DIR,
       {"dir",
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation),
        true}},
      {ConfigEnum::REFRESH_RATE, {"refresh_rate", "", false}},
      {ConfigEnum::RESOLUTION, {"resolution", "1920x1080", true}},
      {ConfigEnum::TAGS, {"tags", "", true}},
      {ConfigEnum::WALLPAPER, {"wallpaper", "", false}},
  };
  QMap<ConfigEnum, QString>* configValues;
};

#endif
