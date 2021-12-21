#include "ScreenStack.h"

#include "Screen.h"

ScreenStack* ScreenStack::instance = NULL;

ScreenStack* ScreenStack::getInstance() {
  return instance;
}

ScreenStack::ScreenStack() {
  instance = this;
}

ScreenStack::~ScreenStack() {
  instance = NULL;
}

void ScreenStack::push(Screen* screen) {
  screens.push(screen);
  screen->show();
}

bool ScreenStack::pop() {
  if (!screens.empty()) {
    screens.pop();

    if (!screens.empty())
      screens.top()->show();

    return true;
  }

  return false;
}
