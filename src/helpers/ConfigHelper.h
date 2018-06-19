#ifndef PARSERS_CONFIGHELPER_H
#define PARSERS_CONFIGHELPER_H

#include <utils/CommonUtils.h>

#include <QObject>
#include <QSettings>
#include <QMap>
#include <QString>
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
  void set(ConfigEnum key, QString value);
  void setWallpaper(QString wallpaper);
  void save();

 private:
  QCoreApplication* app;
  CommonUtils* commonUtils;
  QSettings* settings;
  QMap<ConfigEnum, QStringList> configKeys = {
      {ConfigEnum::DIR,
       {"dir",
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}},
      {ConfigEnum::REFRESH_RATE, {"refresh_rate", ""}},
      {ConfigEnum::RESOLUTION, {"resolution", "1920x1080"}},
      {ConfigEnum::TAGS, {"tags", ""}},
      {ConfigEnum::WALLPAPER, {"wallpaper", ""}},
  };
  QMap<ConfigEnum, QString>* configValues;
};

#endif
