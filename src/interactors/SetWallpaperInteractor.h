#ifndef INTERACTORS_SETWALLPAPERINTERACTOR_H
#define INTERACTORS_SETWALLPAPERINTERACTOR_H

#include "Interactor.h"
#include "helpers/ConfigHelper.h"
#include "helpers/ShellHelper.h"
#include "utils/CommonUtils.h"

#include <QMap>
#include <QString>

class SetWallpaperInteractor : public Interactor {
 public:
  SetWallpaperInteractor(ConfigHelper* configHelper,
                         ShellHelper* shellHelper,
                         CommonUtils* commonUtils);
  void execute();

 private:
  ConfigHelper* configHelper;
  ShellHelper* shellHelper;
  CommonUtils* commonUtils;
  QMap<QString, QString> wallpaperTools = {
      {"qdbus",
       "qdbus org.kde.plasmashell /PlasmaShell "
       "org.kde.PlasmaShell.evaluateScript "
       "\"var allDesktops = desktops();"
       "for (var i = 0; i < allDesktops.length; i++) {"
       "var desktop = allDesktops[i];"
       "desktop.wallpaperPlugin = 'org.kde.image';"
       "desktop.currentConfigGroup = ['Wallpaper', "
       "'org.kde.image', 'General'];"
       "desktop.writeConfig('Image', 'file://:filepath');"
       "}\""},
  };
};

#endif
