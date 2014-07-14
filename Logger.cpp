#include "Logger.h"
#include <string.h>  // Using C version of string
#include <stddef.h>
#include <cstdlib>
#include <iostream>

using namespace std;

std::ofstream Logger::logFile;
int Logger::logLevel;

void Logger::initLogger() {
  Logger::logFile.open(DEFAULT_LOGFILE, ofstream::out | ofstream::app);
  Logger::logLevel = DEFAULT_LOGLEVEL;
  return;
}

void Logger::exitLogger() {
  Logger::logFile.close();
  Logger::logLevel = DEFAULT_LOGLEVEL;
  return;
}

void Logger::setLogfile(const char *str) {
  Logger::logFile.close();
  Logger::logFile.open(str, ofstream::out | ofstream::app);
  return;
}

void Logger::setLogLevel(const char* l) {
  Logger::logLevel = atoi(l);
  return;
}

int Logger::getLogLevel() {
  return Logger::logLevel;
}
