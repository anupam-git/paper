#include <QCoreApplication>
#include <QDebug>

#include <parsers/ArgumentParser.h>

int main(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName(PROJECT_NAME);
  QCoreApplication::setApplicationVersion(PROJECT_VERSION);

  ArgumentParser* argumentParser = new ArgumentParser();
  argumentParser->getParser()->process(app);

  return app.exec();
}
