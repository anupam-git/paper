#include "FetchWallpaperInteractor.h"
#include "helpers/DownloadHelper.h"
#include "helpers/ConfigHelper.h"

#include <QCoreApplication>
#include <QFile>
#include <QUuid>

FetchWallpaperInteractor::FetchWallpaperInteractor(
    ConfigHelper* configHelper,
    CommonUtils* commonUtils,
    SetWallpaperInteractor* setWallpaperInteractor) {
  this->configHelper = configHelper;
  this->commonUtils = commonUtils;
  this->setWallpaperInteractor = setWallpaperInteractor;
}

void FetchWallpaperInteractor::execute() {
  QString resolution = this->configHelper->get(ConfigEnum::RESOLUTION),
          tags = this->configHelper->get(ConfigEnum::TAGS);

  this->commonUtils->say("Downloading Wallpaper");
  this->commonUtils->say("  - Resolution : " + resolution);
  if (tags != "") {
    this->commonUtils->say("  - Tags : " + tags);
  }

  QUrl imageUrl("https://source.unsplash.com/random/" + resolution + "/?" +
                tags);
  this->image = new DownloadHelper(imageUrl);

  connect(this->image, SIGNAL(downloaded()), this, SLOT(downloadFinished()));
}

void FetchWallpaperInteractor::downloadFinished() {
  if (this->configHelper->get(ConfigEnum::WALLPAPER) != "") {
    QFile file(this->configHelper->get(ConfigEnum::DIR) + "/" +
               this->configHelper->get(ConfigEnum::WALLPAPER));
    file.remove();
  }

  QString uuid =
      QUuid::createUuid().toString().replace('{', "").replace('}', "");
  QFile file(this->configHelper->get(ConfigEnum::DIR) + "/" + uuid);
  file.open(QIODevice::WriteOnly);
  file.write(this->image->downloadedData());
  file.close();

  this->configHelper->setWallpaper(uuid);

  this->setWallpaperInteractor->execute();
}
