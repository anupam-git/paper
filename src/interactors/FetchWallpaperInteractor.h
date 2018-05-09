#ifndef INTERACTORS_FETCHWALLPAPERINTERACTOR_H
#define INTERACTORS_FETCHWALLPAPERINTERACTOR_H

#include "Interactor.h"
#include "../helpers/DownloadHelper.h"

class FetchWallpaperInteractor : public Interactor {
  Q_OBJECT

 public:
  FetchWallpaperInteractor();
  void execute();

 private:
  DownloadHelper* image;

 private slots:
  void loadImage();
};

#endif
