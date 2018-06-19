#ifndef UTILS_COMMONUTILS_H
#define UTILS_COMMONUTILS_H

#include <QCoreApplication>
#include <QString>

class CommonUtils {
 private:
  QCoreApplication* app;

 public:
  CommonUtils(QCoreApplication* app);
  void say(QString msg);
  void sayError(QString msg);
};

#endif
