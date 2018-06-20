#ifndef INTERACTORS_FETCHWALLPAPERINTERACTOR_H
#define INTERACTORS_FETCHWALLPAPERINTERACTOR_H

#include "Interactor.h"
#include "SetWallpaperInteractor.h"
#include "helpers/DownloadHelper.h"
#include "helpers/ConfigHelper.h"
#include "utils/CommonUtils.h"

#include <QTimer>

class FetchWallpaperInteractor : public Interactor {
  Q_OBJECT

 public:
  FetchWallpaperInteractor(ConfigHelper* configHelper,
                           CommonUtils* commonUtils,
                           SetWallpaperInteractor* setWallpaperInteractor);
  void execute();

 private:
  DownloadHelper* image;
  ConfigHelper* configHelper;
  CommonUtils* commonUtils;
  SetWallpaperInteractor* setWallpaperInteractor;
  QTimer* timer = nullptr;

 private slots:
  void downloadFinished();
  void timerTimeout();
};

#endif
