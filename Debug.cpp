#include "Debug.h"

const char* Debug::FILENAME = "log.txt";
Debug* Debug::instance = NULL;

Debug::Debug() {
  instance = this;
  logFile = fopen(FILENAME, "w");
}
Debug::~Debug() {
  fclose(logFile);
  instance = NULL;
}

void Debug::Log(const char* format, ...) {
#ifdef LOGS
  va_list args;
  va_start(args, format);
  vfprintf(instance->logFile, format, args);
  va_end(args);

  fputc('\n', instance->logFile);
#endif
}
