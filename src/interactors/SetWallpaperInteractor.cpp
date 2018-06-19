#include "SetWallpaperInteractor.h"

#include <QDebug>

SetWallpaperInteractor::SetWallpaperInteractor(ConfigHelper* configHelper,
                                               ShellHelper* shellHelper,
                                               CommonUtils* commonUtils) {
  this->configHelper = configHelper;
  this->shellHelper = shellHelper;
  this->commonUtils = commonUtils;
}

void SetWallpaperInteractor::execute() {
  QMapIterator<QString, QString> iterator(this->wallpaperTools);

  this->commonUtils->say("");
  this->commonUtils->say("Setting Wallpaper");

  if (this->configHelper->get(ConfigEnum::DOWNLOAD) == "true") {
    this->commonUtils->say("  - Download flag enabled. Not Setting Wallpaper");
  }

  while (iterator.hasNext()) {
    iterator.next();

    if (this->shellHelper->testCommand(iterator.key())) {
      QString cmd = iterator.value();

      cmd.replace(":filepath",
                  this->configHelper->get(ConfigEnum::DIR) + "/" +
                      this->configHelper->get(ConfigEnum::WALLPAPER));
      int returnCode = this->shellHelper->runCommand(cmd);

      if (returnCode > 0) {
        this->commonUtils->say("  - Error Setting Wallpaper");
      } else {
        this->commonUtils->say("  - Wallpaper Set");
      }

      break;
    }
  }

  QCoreApplication::quit();
}
