#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>

#include <cstdio>
#include <cstdlib>

#include <windows.h>

#include "defines.h"

using namespace std;

#define LINE "----------------------------\n"

int clamp(int value, int minValue, int maxValue);

void exit();
bool isExitRequested();
