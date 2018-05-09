#include "DownloadHelper.h"

DownloadHelper::DownloadHelper(QUrl url, QObject* parent) : QObject(parent) {
  this->networkAccessManager = new QNetworkAccessManager();
  this->fileDataAsByteArray = new QByteArray();

  connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this,
          SLOT(fileDownloaded(QNetworkReply*)));

  QNetworkRequest request(url);
  request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

  this->networkAccessManager->get(request);
}

DownloadHelper::~DownloadHelper() {}

void DownloadHelper::fileDownloaded(QNetworkReply* networkReply) {
  *this->fileDataAsByteArray = networkReply->readAll();
  networkReply->deleteLater();

  emit downloaded();
}

QByteArray DownloadHelper::downloadedData() const {
  return *this->fileDataAsByteArray;
}
