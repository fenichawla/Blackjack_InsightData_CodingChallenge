#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <fstream>
#include <unistd.h>

#define DEFAULT_LOGFILE "/tmp/BlackJack.log"
#define DEFAULT_LOGLEVEL 2

#define DEBUG_LOG(l, s) if (l <= Logger::getLogLevel()) { Logger::logFile << "[" << getpid() << "]" << __FILE__ << ":" << __LINE__ << ">>" << s << endl;}

namespace Logger 
{
  extern std::ofstream logFile;
  extern int logLevel;

  void initLogger (void);
  void exitLogger (void);
  void setLogfile (const char*);
  void setLogLevel (const char*);
  int getLogLevel (void);
}


#endif //__LOGGER_H__

