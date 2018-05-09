#include "parsers/ArgumentParser.h"

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName(PROJECT_NAME);
  QCoreApplication::setApplicationVersion(PROJECT_VERSION);

  ArgumentParser* argumentParser = new ArgumentParser();
  argumentParser->process(app.arguments());

  return app.exec();
}
