#include "FetchWallpaperInteractor.h"
#include "../helpers/DownloadHelper.h"

#include <QDebug>
#include <QFile>

FetchWallpaperInteractor::FetchWallpaperInteractor() {}

void FetchWallpaperInteractor::execute() {
  QUrl imageUrl("https://source.unsplash.com/random/1920x1080/?nature");
  this->image = new DownloadHelper(imageUrl);

  connect(this->image, SIGNAL(downloaded()), this, SLOT(loadImage()));
}

void FetchWallpaperInteractor::loadImage() {
  qDebug() << this->image->downloadedData();

  QFile file("/home/anupam/wallpaper");
  file.open(QIODevice::WriteOnly);
  file.write(this->image->downloadedData());
  file.close();
}
