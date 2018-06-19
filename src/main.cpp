#include "parsers/ArgumentParser.h"
#include "interactors/FetchWallpaperInteractor.h"
#include "interactors/SetWallpaperInteractor.h"
#include "utils/CommonUtils.h"
#include "helpers/ConfigHelper.h"
#include "helpers/ShellHelper.h"

#include <QCoreApplication>

int main(int argc, char* argv[]) {
  int returnCode;

  QCoreApplication* app = new QCoreApplication(argc, argv);
  QCoreApplication::setOrganizationName(ORGANISATION_NAME);
  QCoreApplication::setApplicationName(PROJECT_NAME);
  QCoreApplication::setApplicationVersion(PROJECT_VERSION);

  CommonUtils* commonUtils = new CommonUtils(app);
  ConfigHelper* configHelper = new ConfigHelper(app);
  ShellHelper* shellHelper = new ShellHelper();
  ArgumentParser* argumentParser =
      new ArgumentParser(app, commonUtils, configHelper);

  SetWallpaperInteractor* setWallpaperInteractor =
      new SetWallpaperInteractor(configHelper, shellHelper, commonUtils);
  FetchWallpaperInteractor* fetchWallpaperInteractor =
      new FetchWallpaperInteractor(configHelper, commonUtils,
                                   setWallpaperInteractor);

  if ((returnCode = argumentParser->process()) != 0) {
    return returnCode;
  }

  fetchWallpaperInteractor->execute();

  return app->exec();
}
