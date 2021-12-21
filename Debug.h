#pragma once

#include "includes.h"

class Debug {
private:
  static const char* FILENAME;
  static Debug* instance;

  FILE* logFile;

public:
  Debug();
  ~Debug();

  static void Log(const char* format, ...);
};
