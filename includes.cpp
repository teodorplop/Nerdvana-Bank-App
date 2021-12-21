#include "includes.h"

bool exitRequested = false;

int clamp(int value, int minValue, int maxValue) {
  return value < minValue ? minValue : (value > maxValue ? maxValue : value);
}

void exit() {
  exitRequested = true;
}

bool isExitRequested() {
  return exitRequested;
}
