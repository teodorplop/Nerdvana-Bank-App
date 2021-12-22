#include "Screen.h"

Screen::Screen(const string& name, const vector<string>& userActions) {
  this->name = name;
  this->userActions = userActions;
}

void Screen::showTitle() {
  cout << LINE << name << '\n' << LINE;
}

void Screen::showUserActions() {
  unsigned int i;

  for (i = 0; i < userActions.size(); ++i)
    cout << i << " - " << userActions[i] << '\n';

  cout << LINE;
}

void Screen::refresh() {
  isRefreshRequested = true;
  show();
}

void Screen::show() {
  system("cls");

  showTitle();
  showUserActions();
  showInternal();

  isRefreshRequested = false;
  do {
    handleUserAction(waitForInput());
  } while (!isRefreshRequested && !isExitRequested());
}

void Screen::showInternal() {}

void Screen::handleUserAction(const string& action) {}

const string& Screen::waitForInput() {
  unsigned int inputIndex;

  do {
    cin >> inputIndex;
    cin.get();
  } while (inputIndex >= userActions.size());

  return userActions[inputIndex];
}
