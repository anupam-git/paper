#include "CommonUtils.h"

#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>

using namespace std;

CommonUtils::CommonUtils(QCoreApplication* app) {
  this->app = app;
}

void CommonUtils::say(QString msg) {
  QTextStream out(stdout);
  out << msg << endl;
}

void CommonUtils::sayError(QString err) {
  qWarning() << "ERROR :" << err;

  this->app->exit(1);
}
