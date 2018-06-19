#include "ShellHelper.h"

ShellHelper::ShellHelper() {}

int ShellHelper::runCommand(QString cmd) {
  cmd = cmd + " | sed -e 's/^/  - /'";
  return system(cmd.toStdString().c_str());
}

bool ShellHelper::testCommand(QString cmd) {
  cmd = "command -v " + cmd + " > /dev/null 2>&1";
  return system(cmd.toStdString().c_str()) == 0;
}
