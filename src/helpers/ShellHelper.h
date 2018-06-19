#ifndef HELPERS_SHELLHELPER_H
#define HELPERS_SHELLHELPER_H

#include <QString>

class ShellHelper {
 public:
  ShellHelper();
  int runCommand(QString cmd);
  bool testCommand(QString cmd);
};

#endif
