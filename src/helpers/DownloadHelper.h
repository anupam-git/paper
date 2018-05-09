#ifndef HELPERS_DOWNLOADHELPER_H
#define HELPERS_DOWNLOADHELPER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class DownloadHelper : public QObject {
  Q_OBJECT
 public:
  explicit DownloadHelper(QUrl imageUrl, QObject* parent = 0);
  virtual ~DownloadHelper();
  QByteArray downloadedData() const;

 signals:
  void downloaded();

 private slots:
  void fileDownloaded(QNetworkReply* networkReply);

 private:
  QNetworkAccessManager* networkAccessManager;
  QByteArray* fileDataAsByteArray;
};

#endif
