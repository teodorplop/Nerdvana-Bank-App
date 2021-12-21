#pragma once

#include "includes.h"

class Screen;

class ScreenStack {
private:
  static ScreenStack* instance;

  stack<Screen*> screens;

public:
  static ScreenStack* getInstance();

  ScreenStack();
  ~ScreenStack();

  void push(Screen* screen);
  bool pop();
};
