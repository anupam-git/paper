#ifndef PARSER_ARGUMENTPARSER_H
#define PARSER_ARGUMENTPARSER_H

#include <QCommandLineParser>

class ArgumentParser {
 private:
  QCommandLineParser* parser;

 public:
  ArgumentParser();
  QCommandLineParser* getParser();
};

#endif
